/*
 * Copyright 2008, Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based vaguely on the Linux code
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <errno.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <linux/list.h>
#include <div64.h>
#include <asm/arch/rtkemmc.h>

extern int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data);
extern void mmc_set_bus_width(struct mmc *mmc, uint width);

extern struct list_head mmc_devices;
extern int cur_dev_num;

/* frequency bases */
/* divided by 10 to be nice to platforms without floating point */
static const int fbase[] = {
	10000,
	100000,
	1000000,
	10000000,
};

/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
static const int multipliers[] = {
	0,	/* reserved */
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80,
};

/**************************************************************************
*	This part of code is for SD card.  All functions are                  *
*	copied from MMC framework and modify the argument to fit              *
*	SD card specification. This part might be merged into MMC             *
*	framework one day in the future. Currently, separate SD               *
*	code from MMC framework for debugging easier                          *
*	EMMC device number is 0 and SD card device number is 1                *
*	However, in the source code, we did not use device number             *
*	to search the SD card device, we use device type,                     *
*       so fatload sd x:1 the variable x does not have impact on          *
*	SD card search                                                        *
***************************************************************************/
#define R1_STATE_IDLE	0
#define R1_STATE_READY	1
#define R1_STATE_IDENT	2
#define R1_STATE_STBY	3
#define R1_STATE_TRAN	4
#define R1_STATE_DATA	5
#define R1_STATE_RCV	6
#define R1_STATE_PRG	7
#define R1_STATE_DIS	8

/* CPU-specific MMC initializations */
__weak int cpu_sd_init(bd_t *bis)
{
	return -1;
}

/* board-specific MMC initializations. */
__weak int board_sd_init(bd_t *bis)
{
	return -1;
}

struct mmc *find_sd_device(void);
int sd_send_status(struct mmc *mmc, int timeout);
int sd_app_set_bus_width(struct mmc *mmc);

#ifdef CONFIG_PARTITIONS
block_dev_desc_t *sd_get_dev(int dev)
{
	struct mmc *mmc = find_sd_device();
	if (!mmc) {
		printf("No SD card in slot...\n");
		return NULL;
	}
	if (sd_init(mmc)==0) {
		return &mmc->block_dev;
	}
	else {
		return NULL;
	}
}
#endif

static int sd_switch_with_flags(struct mmc *mmc, int mode, int group, u8 value, u8 *resp)
{
        struct mmc_cmd cmd;
        struct mmc_data data;
        /* Switch the frequency */
        cmd.opcode = SD_CMD_SWITCH_FUNC;
        cmd.resp_type = MMC_RSP_R1;
        cmd.arg = (mode << 31) | 0xffffff;
        cmd.arg &= ~(0xf << (group * 4));
        cmd.arg |= value << (group * 4);
        //cmd.flags = 0;   //jim comment
        cmd.flags = 0xb5;   //jim add
        data.dest = (char *)resp;
        data.blocksize = 64;
        data.blocks = 1;
        data.flags = MMC_DATA_READ;

        return mmc_send_cmd(mmc, &cmd, &data);
}

int sd_read_blocks(struct mmc *mmc, void *dst, ulong start, lbaint_t blkcnt)
{
        struct mmc_cmd cmd;
        struct mmc_data data;
        if (blkcnt > 1)
                cmd.opcode = MMC_CMD_READ_MULTIPLE_BLOCK;
        else
                cmd.opcode = MMC_CMD_READ_SINGLE_BLOCK;

        if (mmc->high_capacity)
                cmd.arg = start;
        else
                cmd.arg = start * mmc->read_bl_len;

        cmd.resp_type = MMC_RSP_R1;
        //cmd.flags = 0;
        cmd.flags = 0xb5;       //change this flag
        data.dest = dst;
        data.blocks = blkcnt;
        data.blocksize = mmc->read_bl_len;
        data.flags = MMC_DATA_READ;

        if (mmc_send_cmd(mmc, &cmd, &data))
                return 0;

        if (blkcnt > 1) {
                cmd.opcode = MMC_CMD_STOP_TRANSMISSION;
                cmd.arg = 0;
                cmd.resp_type = MMC_RSP_R1B;
                cmd.flags = 0;
                if (mmc_send_cmd(mmc, &cmd, NULL)) {
                        return 0;
                }
        }

        return blkcnt;
}

static ulong sd_bread(int dev_num, ulong start, lbaint_t blkcnt, void *dst)
{
        lbaint_t cur, blocks_todo = blkcnt;

        if (blkcnt == 0)
                return 0;

        struct mmc *mmc = find_sd_device();
        if (!mmc)
                return 0;

        if ((start + blkcnt) > mmc->block_dev.lba) {
                printf("MMC: %s %d, block number 0x%lx exceeds max(0x%lx)\n", __FUNCTION__, __LINE__,
                        start + blkcnt, mmc->block_dev.lba);
                return 0;
        }

        do {
                cur = (blocks_todo > mmc->b_max) ?  mmc->b_max : blocks_todo;
                if(sd_read_blocks(mmc, dst, start, cur) != cur) {
                        return 0;
                }
                blocks_todo -= cur;
                start += cur;
                dst += cur * mmc->read_bl_len;
        } while (blocks_todo > 0);

        return blkcnt;
}

static ulong
sd_write_blocks(struct mmc *mmc, ulong start, lbaint_t blkcnt, const void*src)
{
        struct mmc_cmd cmd;
        struct mmc_data data;
        int timeout = 1000;


        if ((start + blkcnt) > mmc->block_dev.lba) {
                printf("MMC: %s %d, block number 0x%lx exceeds max(0x%lx)\n", __FUNCTION__, __LINE__,
                        start + blkcnt, mmc->block_dev.lba);
                return 0;
        }
        if (blkcnt > 1)
                cmd.opcode = MMC_CMD_WRITE_MULTIPLE_BLOCK;
        else
                cmd.opcode = MMC_CMD_WRITE_SINGLE_BLOCK;

        if (mmc->high_capacity)
                cmd.arg = start;
        else
                cmd.arg = start * mmc->write_bl_len;

        cmd.resp_type = MMC_RSP_R1;
//      cmd.flags = 0;
        cmd.flags = 0xb5;       //change this flags

        data.src = src;
        data.blocks = blkcnt;
        data.blocksize = mmc->write_bl_len;
        data.flags = MMC_DATA_WRITE;

        if (mmc_send_cmd(mmc, &cmd, &data)) {
                return 0;
        }
	// SPI multiblock writes terminate using a special
        // token, not a STOP_TRANSMISSION request.

        if (!mmc_host_is_spi(mmc) && blkcnt > 1) {
                cmd.opcode = MMC_CMD_STOP_TRANSMISSION;
                cmd.arg = 0;
                cmd.resp_type = MMC_RSP_R1B;
                cmd.flags = 0;
                if (mmc_send_cmd(mmc, &cmd, NULL)) {
                        return 0;
                }
        }

        // Waiting for the ready status
        if (sd_send_status(mmc, timeout))
                return 0;

        return blkcnt;
}

static ulong
sd_bwrite(int dev_num, ulong start, lbaint_t blkcnt, const void*src)
{
        lbaint_t cur, blocks_todo = blkcnt;

        struct mmc *mmc = find_sd_device();
        if (!mmc)
                return 0;

        do {
                cur = (blocks_todo > mmc->b_max) ?  mmc->b_max : blocks_todo;
                if(sd_write_blocks(mmc, start, cur, src) != cur) {
                        return 0;
                }
                blocks_todo -= cur;
                start += cur;
                src += cur * mmc->write_bl_len;
        } while (blocks_todo > 0);

        return blkcnt;
}

ulong rtk_sd_read(ulong start, lbaint_t blkcnt, void *dst)
{
	//DDDDYELLOW("%s: %ld, %ld, %p\n", __FUNCTION__, start, blkcnt, dst);
	return sd_bread(0, start, blkcnt, dst);
}

ulong
rtk_sd_write(ulong start, lbaint_t blkcnt, const void*src)
{
	//DDDDYELLOW("%s: %ld, %ld, %p\n", __FUNCTION__, start, blkcnt, src);
	return sd_bwrite(0, start, blkcnt, src);
}

int sd_send_status(struct mmc *mmc, int timeout)
{
        struct mmc_cmd cmd;
        int err, retries = 5;
#ifdef CONFIG_MMC_TRACE
        int status;
#endif

        cmd.opcode = MMC_CMD_SEND_STATUS;
        cmd.flags = 0x195;	//change this flag
        if (!mmc_host_is_spi(mmc))
                cmd.arg = mmc->rca << 16;

        do {
                err = mmc_send_cmd(mmc, &cmd, NULL);
                if (!err) {
                        if ((cmd.resp[0] & MMC_STATUS_RDY_FOR_DATA) &&
                            R1_CURRENT_STATE(cmd.resp[0]) != R1_STATE_PRG)
                                break;
                        else if (cmd.resp[0] & MMC_STATUS_MASK) {
                                printf("Status Error: 0x%08X\n",
                                        cmd.resp[0]);
                                return COMM_ERR;
                        }
                } else if (--retries < 0)
                        return err;

                udelay(1000);

        } while (timeout--);

#ifdef CONFIG_MMC_TRACE
        status = (cmd.resp[0] & MMC_STATUS_CURR_STATE) >> 9;
        printf("CURR STATE:%d\n", status);
#endif
        if (!timeout) {
                printf("Timeout waiting card ready\n");
                return TIMEOUT;
        }

        return 0;
}

int sd_go_idle(struct mmc* mmc)
{
        struct mmc_cmd cmd;
        int err, i;

        udelay(1000);

        cmd.opcode = MMC_CMD_GO_IDLE_STATE;
        cmd.arg = 0;
        cmd.resp_type = MMC_RSP_NONE;
        cmd.flags = 0xc0;

		for (i = 0; i < 5; i++)
			err = mmc_send_cmd(mmc, &cmd, NULL);

        if (err) {
			return err;
        }

        udelay(2000);

        return 0;
}

int sd_send_if_cond(struct mmc *mmc)
{
        struct mmc_cmd cmd;
        int err;

        cmd.opcode = SD_CMD_SEND_IF_COND;
        // We set the bit if the host supports voltages between 2.7 and 3.6 V
        cmd.arg = ((mmc->voltages & 0xff8000) != 0) << 8 | 0xaa;
        cmd.resp_type = MMC_RSP_R7;

        //cmd.flags = 0;
        cmd.flags = 0x2f5;    //change this flag

        err = mmc_send_cmd(mmc, &cmd, NULL);

        if (err)
                return err;

        if ((cmd.resp[0] & 0xff) != 0xaa)
                return UNUSABLE_ERR;
        else
                mmc->version = SD_VERSION_2;

        return 0;
}

int sd_CR_send_op_cond(struct mmc *mmc)
{
	int timeout = 1000;
	int err;
	struct mmc_cmd cmd;

	do {
		cmd.opcode = MMC_CMD_APP_CMD;    //cmd 55
		cmd.resp_type = MMC_RSP_R1;
		cmd.arg = 0;
		//      cmd.flags = 0;
		cmd.flags = 0xf5;	//change this flag

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err){
			return err;
		}

		cmd.opcode = SD_CMD_APP_SEND_OP_COND;   //cmd 41
		cmd.resp_type = MMC_RSP_R3;


		// Most cards do not answer if some reserved bits
		// in the ocr are set. However, Some controller
		// can set bit 7 (reserved for low voltages), but
		// how to manage low voltages SD card is not yet
		// specified.

		cmd.arg = mmc_host_is_spi(mmc) ? 0 :
		(mmc->voltages & 0xff8000);

		if (mmc->version == SD_VERSION_2)
			cmd.arg |= OCR_HCS;

		//==========Modify the command argumnet=============
		cmd.arg |= 0x4120;
		cmd.arg = cmd.arg <<16;
		cmd.flags=0xe1;
		//==================================================
		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		udelay(1000);
	} while ((!(cmd.resp[0] & OCR_BUSY)) && timeout--);

	if (timeout <= 0) {
		return UNUSABLE_ERR;
	}

	if (mmc->version != SD_VERSION_2) {
		mmc->version = SD_VERSION_1_0;
	}

	if (mmc_host_is_spi(mmc)) { // read OCR for spi
		cmd.opcode = MMC_CMD_SPI_READ_OCR;
		cmd.resp_type = MMC_RSP_R3;
		cmd.arg = 0;
		cmd.flags = 0;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;
	}

	mmc->ocr = cmd.resp[0];

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 0;

	return 0;
}

int sd_app_send_status(struct mmc *mmc, int timeout)
{
        struct mmc_cmd cmd;

        //======Add this DMA ======
	MY_CLR_ALIGN_BUFFER();
        MY_ALLOC_CACHE_ALIGN_BUFFER(uint, Status, 2);
        struct mmc_data data;
        //==========================

        int err, retries = 5;

#ifdef CONFIG_MMC_TRACE
        int status;
#endif
        //=========cmd 55 ========
         if (mmc_host_is_spi(mmc))
                return 0;

        // Read the SCR to find out if this card supports higher speeds
        cmd.opcode = MMC_CMD_APP_CMD;
        cmd.resp_type = MMC_RSP_R1;
        cmd.arg = mmc->rca << 16;
        cmd.flags = 0x95;
        err = mmc_send_cmd(mmc, &cmd, NULL);
        if (err)
                return err;
        //=============================================

        cmd.opcode = MMC_CMD_SEND_STATUS;	//acmd13
        cmd.resp_type = MMC_RSP_R1;
        if (!mmc_host_is_spi(mmc))
                cmd.arg = mmc->rca << 16;
        cmd.arg =0;     //fit the same behavior with linux SD card driver
        //cmd.flags = 0;
        cmd.flags = 0x1b5;

        //=======ADD this part=============
        data.dest = (char *)Status;
        data.blocksize = 64;
        data.blocks = 1;
        data.flags = MMC_DATA_READ;
        //=================================
		do {
                err = mmc_send_cmd(mmc, &cmd, &data);     //Acmd 13 is stream cmd
                if (!err) {
                        if ((cmd.resp[0] & MMC_STATUS_RDY_FOR_DATA) &&
                            R1_CURRENT_STATE(cmd.resp[0]) != R1_STATE_PRG)
                                break;
                        else if (cmd.resp[0] & MMC_STATUS_MASK) {
                                printf("Status Error: 0x%08X\n",
                                        cmd.resp[0]);
                                return COMM_ERR;
                        }
                } else if (--retries < 0) {
                        printf("error: retries<0\n");
                        return err;
                }

                udelay(1000);

        } while (timeout--);

#ifdef CONFIG_MMC_TRACE
        status = (cmd.resp[0] & MMC_STATUS_CURR_STATE) >> 9;
        printf("CURR STATE:%d\n", status);
#endif
        if (!timeout) {
                printf("Timeout waiting card ready\n");
                return TIMEOUT;
        }

        return 0;
}

#ifdef CONFIG_SD30
void sd_update_bus_speed_mode(struct mmc *mmc)
{
	if ((mmc->host_caps & MMC_CAP_UHS_SDR104) &&
            (mmc->sd_bus_mode & SD_MODE_UHS_SDR104))
		mmc->sd_bus_speed = UHS_SDR104_BUS_SPEED;
	else if ((mmc->host_caps & (MMC_CAP_UHS_SDR104 |
                    MMC_CAP_UHS_SDR50)) && (mmc->sd_bus_mode &
                    SD_MODE_UHS_SDR50))
		mmc->sd_bus_speed = UHS_SDR50_BUS_SPEED;
	else
		mmc->sd_bus_speed = -1;	//invalid SD 3.0 card
}

int mmc_sd_init_uhs_card(struct mmc *mmc)
{
	int err = 0;
	MY_CLR_ALIGN_BUFFER();
	MY_ALLOC_CACHE_ALIGN_BUFFER(uint, switch_status, 16);
	u8 *status = (u8 *)(switch_status);

	err = sd_app_set_bus_width(mmc);
	if (err) {
		printf("sd_app_set_bus_width error(%d)\n", err);
		return err;
	}

	sd_update_bus_speed_mode(mmc);

	switch (mmc->sd_bus_speed) {
	case UHS_SDR104_BUS_SPEED:
		mmc->tran_speed = 208000000;
		break;
	case UHS_SDR50_BUS_SPEED:
		mmc->tran_speed = 100000000;
		break;
	default:
		printf("invalid SD 3.0 card...\n");
		return -1;
	}

	err = sd_switch_with_flags(mmc, 1, 0, mmc->sd_bus_speed, (u8 *)switch_status);
	if (err) {
		printf("sd_switch_with_flags to SD 3.0 voltage failed...\n");
                return err;
	}

	if((status[16] & 0xF) != mmc->sd_bus_speed)
		printf("Problem setting bus speed mode!\n");
	else {
		mmc_set_clock(mmc, mmc->tran_speed);
	}

	if(mmc->execute_tuning) {
		mmc->execute_tuning(mmc,MMC_SEND_TUNING_BLOCK);
	}
	else {
		printf("SD host driver does not implement execute tuning function...\n");
		return -1;
	}

	return 0;
}
#endif /* CONFIG_SD30 */

int sd_CR_change_freq(struct mmc *mmc)
{
        int err;
        struct mmc_cmd cmd;
	MY_CLR_ALIGN_BUFFER();
        MY_ALLOC_CACHE_ALIGN_BUFFER(uint, scr, 2);
        MY_ALLOC_CACHE_ALIGN_BUFFER(uint, switch_status, 16);
        struct mmc_data data;
        int timeout;

        mmc->card_caps = 0;

        if (mmc_host_is_spi(mmc))
                return 0;

        // Read the SCR to find out if this card supports higher speeds
        cmd.opcode = MMC_CMD_APP_CMD;          //cmd 55
        cmd.resp_type = MMC_RSP_R1;
        cmd.arg = mmc->rca << 16;
//      cmd.flags = 0;
        cmd.flags = 0x95;     //Modify the flags
        err = mmc_send_cmd(mmc, &cmd, NULL);

        if (err)
                return err;

        cmd.opcode = SD_CMD_APP_SEND_SCR;      //cmd 51
        cmd.resp_type = MMC_RSP_R1;
        cmd.arg = 0;
        //cmd.flags = 0;
        cmd.flags = 0xb5;    //Modify the flags

        timeout = 3;

retry_scr:
        data.dest = (char *)scr;
        data.blocksize = 8;
        data.blocks = 1;
        data.flags = MMC_DATA_READ;

        err = mmc_send_cmd(mmc, &cmd, &data);

        if (err) {
                if (timeout--)
                        goto retry_scr;

                return err;
        }

        mmc->scr[0] = __be32_to_cpu(scr[0]);
        mmc->scr[1] = __be32_to_cpu(scr[1]);

        printf("mmc->scr[0]=%x,mmc->scr[1]=%x\n", mmc->scr[0], mmc->scr[1]);
	switch ((mmc->scr[0] >> 24) & 0xf) {
                case 0:
                        mmc->version = SD_VERSION_1_0;
                        break;
                case 1:
                        mmc->version = SD_VERSION_1_10;
                        break;
                case 2:
                        mmc->version = SD_VERSION_2;
                        break;
                default:
                        mmc->version = SD_VERSION_1_0;
                        break;
        }

        if (mmc->scr[0] & SD_DATA_4BIT)
                mmc->card_caps |= MMC_MODE_4BIT;

        // Waiting for the ready status, ACMD13 to fit the SD card cmd procedure
        err = sd_app_send_status(mmc, timeout);

        if (err) {
                return err;
        }

        // Version 1.0 doesn't support switching
        if (mmc->version == SD_VERSION_1_0)
                return 0;

        timeout = 4;
        while (timeout--) {	//cmd 6
                err = sd_switch_with_flags(mmc, SD_SWITCH_CHECK, 0, 0,
                                (u8 *)switch_status);

                if (err)
                        return err;

#ifdef CONFIG_SD30
                if(mmc->ocr & SD_ROCR_S18A) {
                        u8 *status = (u8 *)switch_status;
                        mmc->sd_bus_mode = status[13];
                        /* Driver Strengths supported by the card */
                        //mmc->sd_drv_type = status[9];
                        //printf("SD 3.0 mode, sd_bus_mode = %x, mmc->ocr =%x\n",mmc->sd_bus_mode, mmc->ocr);
                }
#endif /* CONFIG_SD30 */
                // The high-speed function is busy.  Try again
                if (!(__be32_to_cpu(switch_status[7]) & SD_HIGHSPEED_BUSY))
                        break;
        }

        // If high-speed isn't supported, we return
        if (!(__be32_to_cpu(switch_status[3]) & SD_HIGHSPEED_SUPPORTED))
                return 0;

         // If the host doesn't support SD_HIGHSPEED, do not switch card to
         // HIGHSPEED mode even if the card support SD_HIGHSPPED.
         // This can avoid furthur problem when the card runs in different
         // mode between the host.

        if (!((mmc->host_caps & MMC_MODE_HS_52MHz) &&
                (mmc->host_caps & MMC_MODE_HS)))
		{
			return 0;
		}
#ifdef CONFIG_SD30
	if( (mmc->ocr & SD_ROCR_S18A) )
	{
		err = mmc_sd_init_uhs_card(mmc);
		if (err) {
			printf("SD: mmc_sd_init_uhs_card fail(%d)", err);
        	return err;;
        }
	}
	else
#endif /* CONFIG_SD30 */
	{
		err = sd_switch_with_flags(mmc, SD_SWITCH_SWITCH, 0, 1, (u8 *)switch_status);
		if (err) {
			printf("SD: sd_switch_with_flags fail(%d)", err);
			return err;
		}

		if ((__be32_to_cpu(switch_status[4]) & 0x0f000000) == 0x01000000) {
			mmc->card_caps |= MMC_MODE_HS;
		}

		mmc_set_clock(mmc, 50000000);
		err = sd_app_set_bus_width(mmc);
		if (err) {
			printf("SD: sd_app_set_bus_width fail(%d)", err);
			return err;
		}
	}

	return 0;
}

int sd_app_set_bus_width(struct mmc *mmc)
{
	int err = 0;
	struct mmc_cmd cmd;

	mmc->erase_grp_size = 1;
	mmc->part_config = MMCPART_NOAVAILABLE;
    // Restrict card's capabilities by what the host can do
	mmc->card_caps &= mmc->host_caps;

	if (IS_SD(mmc)) {
		if (mmc->card_caps & MMC_MODE_4BIT) {
			cmd.opcode = MMC_CMD_APP_CMD;    //cmd 55
			cmd.resp_type = MMC_RSP_R1;
			cmd.arg = mmc->rca << 16;
			//cmd.flags = 0;
			cmd.flags = 0x95;   //change the flags

			err = mmc_send_cmd(mmc, &cmd, NULL);
			if (err) {
				printf("SD: mmc_send_cmd MMC_CMD_APP_CMD err %d", err);
				return err;
			}

			cmd.opcode = SD_CMD_APP_SET_BUS_WIDTH;   //Acmd 6
			cmd.resp_type = MMC_RSP_R1;
			cmd.arg = 2;
			//cmd.flags = 0;
			cmd.flags = 0x15;   //change the flags
			err = mmc_send_cmd(mmc, &cmd, NULL);
			if (err) {
				printf("SD: mmc_send_cmd SD_CMD_APP_SET_BUS_WIDTH err %d", err);
				return err;
			}

			mmc_set_bus_width(mmc, 4);
		}

		if (mmc->card_caps & MMC_MODE_HS)
			mmc->tran_speed = 50000000;
		else
			mmc->tran_speed = 25000000;
	}
	else {

	}

	mmc_set_clock(mmc, mmc->tran_speed);
	return 0;
}

int sd_startup(struct mmc *mmc)
{
        int err;
        uint mult, freq;
        u64 cmult, csize;
        struct mmc_cmd cmd;
	MY_CLR_ALIGN_BUFFER();
        //MY_ALLOC_CACHE_ALIGN_BUFFER(char, ext_csd, 512);
        //MY_ALLOC_CACHE_ALIGN_BUFFER(char, test_csd, 512);
        //int timeout = 1000;

#ifdef CONFIG_MMC_SPI_CRC_ON
        if (mmc_host_is_spi(mmc)) { /// enable CRC check for spi
                cmd.opcode = MMC_CMD_SPI_CRC_ON_OFF;
                cmd.resp_type = MMC_RSP_R1;
                cmd.arg = 1;
                cmd.flags = 0;
                err = mmc_send_cmd(mmc, &cmd, NULL);

                if (err)
                        return err;
        }
#endif

        // Put the Card in Identify Mode
        cmd.opcode = mmc_host_is_spi(mmc) ? MMC_CMD_SEND_CID :     //cmd 2
                MMC_CMD_ALL_SEND_CID; // cmd not supported in spi
        cmd.resp_type = MMC_RSP_R2;
        cmd.arg = 0;
//      cmd.flags = 0;    //jim comment
        cmd.flags = 0x67;   //jim add

        err = mmc_send_cmd(mmc, &cmd, NULL);

        if (err)
                return err;

        memcpy(mmc->cid, cmd.resp, 16);

         // For MMC cards, set the Relative Address.
         // For SD cards, get the Relatvie Address.
         // This also puts the cards into Standby State

        if (!mmc_host_is_spi(mmc)) { // cmd not supported in spi
                cmd.opcode = SD_CMD_SEND_RELATIVE_ADDR;   //cmd 3
                cmd.arg = mmc->rca << 16;
                cmd.resp_type = MMC_RSP_R6;
                //cmd.flags = 0;
                cmd.flags = 0x75;	//change the flags

                err = mmc_send_cmd(mmc, &cmd, NULL);

                if (err)
                        return err;

                if (IS_SD(mmc))
                        mmc->rca = (cmd.resp[0] >> 16) & 0xffff;
        }

        // Get the Card-Specific Data
        cmd.opcode = MMC_CMD_SEND_CSD;   //cmd 9
        cmd.resp_type = MMC_RSP_R2;
        cmd.arg = mmc->rca << 16;
//      cmd.flags = 0;
        cmd.flags = 0x7;   //chnage the flags

	err = mmc_send_cmd(mmc, &cmd, NULL);

        mmc->csd[0] = cmd.resp[0];
        mmc->csd[1] = cmd.resp[1];
        mmc->csd[2] = cmd.resp[2];
        mmc->csd[3] = cmd.resp[3];
        if (mmc->version == MMC_VERSION_UNKNOWN) {
                int version = (cmd.resp[0] >> 26) & 0xf;

                switch (version) {
                        case 0:
                                mmc->version = MMC_VERSION_1_2;
                                break;
                        case 1:
                                mmc->version = MMC_VERSION_1_4;
                                break;
                        case 2:
                                mmc->version = MMC_VERSION_2_2;
                                break;
                        case 3:
                                mmc->version = MMC_VERSION_3;
                                break;
                        case 4:
                                mmc->version = MMC_VERSION_4;
                                break;
                        default:
                                mmc->version = MMC_VERSION_1_2;
                                break;
                }
        }
        // divide frequency by 10, since the mults are 10x bigger
        freq = fbase[(cmd.resp[0] & 0x7)];
        mult = multipliers[((cmd.resp[0] >> 3) & 0xf)];

        mmc->tran_speed = freq * mult;

        mmc->read_bl_len = 1 << ((cmd.resp[1] >> 16) & 0xf);

        if (IS_SD(mmc))
                mmc->write_bl_len = mmc->read_bl_len;
        else
                mmc->write_bl_len = 1 << ((cmd.resp[3] >> 22) & 0xf);

        if (mmc->high_capacity) {
                csize = (mmc->csd[1] & 0x3f) << 16
                        | (mmc->csd[2] & 0xffff0000) >> 16;
                cmult = 8;
        } else {
                csize = (mmc->csd[1] & 0x3ff) << 2
                        | (mmc->csd[2] & 0xc0000000) >> 30;
                cmult = (mmc->csd[2] & 0x00038000) >> 15;
        }
	mmc->capacity = (csize + 1) << (cmult + 2);
        mmc->capacity *= mmc->read_bl_len;
        //printf("mmc->read_bl_len = %d,  mmc->write_bl_len=%d\n",mmc->read_bl_len,mmc->write_bl_len);
        if (mmc->read_bl_len > 512)
                mmc->read_bl_len = 512;

        if (mmc->write_bl_len > 512)
                mmc->write_bl_len = 512;

        // Select the card, and put it into Transfer Mode
        if (!mmc_host_is_spi(mmc)) { // cmd not supported in spi
                cmd.opcode = MMC_CMD_SELECT_CARD;    //cmd 7
                cmd.resp_type = MMC_RSP_R1;
                cmd.arg = mmc->rca << 16;
                //cmd.flags = 0;
                cmd.flags = 0x15;   //change the flags
                err = mmc_send_cmd(mmc, &cmd, NULL);
                if (err)
                        return err;
        }
        mmc_set_clock(mmc, 6200000);
        //acmd 51 to read scr
        err = sd_CR_change_freq(mmc);

        if (err)
                return err;

 /*       mmc_set_clock(mmc, 50000000);

        // For SD, its erase group is always one sector

        mmc->erase_grp_size = 1;
        mmc->part_config = MMCPART_NOAVAILABLE;
        // Restrict card's capabilities by what the host can do
        mmc->card_caps &= mmc->host_caps;

        if (IS_SD(mmc)) {
                if (mmc->card_caps & MMC_MODE_4BIT) {
                        cmd.opcode = MMC_CMD_APP_CMD;    //cmd 55
                        cmd.resp_type = MMC_RSP_R1;
                        cmd.arg = mmc->rca << 16;
                        //cmd.flags = 0;
                        cmd.flags = 0x95;   //change the flags

                        err = mmc_send_cmd(mmc, &cmd, NULL);
                        if (err)
                                return err;

                        cmd.opcode = SD_CMD_APP_SET_BUS_WIDTH;   //Acmd 6
                        cmd.resp_type = MMC_RSP_R1;
                        cmd.arg = 2;
                        //cmd.flags = 0;
                        cmd.flags = 0x15;   //change the flags
                        err = mmc_send_cmd(mmc, &cmd, NULL);
                        if (err)
                                return err;

                        mmc_set_bus_width(mmc, 4);
                }

                if (mmc->card_caps & MMC_MODE_HS)
                        mmc->tran_speed = 50000000;
                else
                        mmc->tran_speed = 25000000;
        } else {
        }

        mmc_set_clock(mmc, mmc->tran_speed);
*/
        // fill in device description
        mmc->block_dev.lun = 0;
        mmc->block_dev.type = 0;
        mmc->block_dev.blksz = mmc->read_bl_len;
        mmc->block_dev.lba = lldiv(mmc->capacity, mmc->read_bl_len);
	 sprintf(mmc->block_dev.vendor, "Man %06x Snr %08x", mmc->cid[0] >> 8,
                        (mmc->cid[2] << 8) | (mmc->cid[3] >> 24));
        sprintf(mmc->block_dev.product, "%c%c%c%c%c", mmc->cid[0] & 0xff,
                        (mmc->cid[1] >> 24), (mmc->cid[1] >> 16) & 0xff,
                        (mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);
        sprintf(mmc->block_dev.revision, "%d.%d", mmc->cid[2] >> 28,
                        (mmc->cid[2] >> 24) & 0xf);
        init_part(&mmc->block_dev);

        return 0;
}


struct mmc *find_sd_device()
{
	struct mmc *m;
	struct list_head *entry;

	list_for_each(entry, &mmc_devices) {
		m = list_entry(entry, struct mmc, link);
		if (m->block_dev.if_type == IF_TYPE_SD) {
	    	return m;
	    }
	}

	printf("SD Device not found\n");

	return NULL;
}

int sd_initialize(bd_t *bis)
{
	if (mmc_devices.next == NULL && mmc_devices.prev == NULL)
		INIT_LIST_HEAD (&mmc_devices);
	cur_dev_num = 0;

	if (board_sd_init(bis) < 0) {
		cpu_sd_init(bis);
	}
#if 0 /* not support generic flow */
  #ifndef CONFIG_SPL_BUILD
	print_mmc_devices(',');
  #endif
	do_preinit();
#endif
	return 0;
}

// must be executed after sd_initialize
int sd_card_init(void)
{
	struct mmc *mmc;
	int curr_sd_device_id;

	if (get_mmc_num() > 0)
		curr_sd_device_id = 0;
	else {
		printf("No SD device available(%d)\n", get_mmc_num());
		return -1;
	}

	mmc = find_sd_device();

	if (!mmc) {
		printf("no SD device at slot %x\n", curr_sd_device_id);
		return -2;
	}
	mmc->has_init = 0;

	if (sd_init(mmc)!=0) {
		printf("initialize SD device at slot %x failed\n", curr_sd_device_id);
		return -3; /* error */
	}
	else {
		return 0; /* successful */
	}
}

int sd_register(struct mmc *mmc)
{
	// Setup the universal parts of the block interface just once
	//SD card will be registered after mmc, by default, emmc is 0 and SD card is 1
	mmc->block_dev.if_type = IF_TYPE_SD;
	mmc->block_dev.part_type = PART_TYPE_UNKNOWN;
	mmc->block_dev.type = DEV_TYPE_HARDDISK;
	mmc->block_dev.dev = cur_dev_num++;
	mmc->block_dev.removable = 1;

	printf("SD device index# %d\n", mmc->block_dev.dev);

	mmc->block_dev.block_read = sd_bread;
	mmc->block_dev.block_write = sd_bwrite;
	//mmc->block_dev.block_erase = sd_berase;
	if (!mmc->b_max)
		mmc->b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT;

	INIT_LIST_HEAD (&mmc->link);

	list_add_tail (&mmc->link, &mmc_devices);

	return 0;
}

//========= for SD 3.0 mode: TBD ===========

int sd_set_signal_voltage(struct mmc *mmc, u32 voltage)
{
#ifdef CONFIG_SD30
	struct mmc_cmd cmd = {0};
	int err = 0;
	u32 clock;

	/*
	* Send CMD11 only if the request is to switch the card to
	* 1.8V signalling.
	*/
	if (voltage == MMC_SIGNAL_VOLTAGE_330)
		return -1;

	/*
	* If we cannot switch voltages, return failure so the caller
	* can continue without UHS mode
	*/
	if (!mmc->switch_voltage) {
		printf("SD host driver does not support SD 3.0\n");
		return -1;
	}

	cmd.opcode = SD_SWITCH_VOLTAGE;
	cmd.arg = 0;
	cmd.flags = 0x15;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if(err) {
		printf("switch voltage cmd 11 error...\n");
		return -1;
	}

	if (!mmc_host_is_spi(mmc) && (cmd.resp[0] & R1_ERROR)) {
		printf("switch voltage response 1 error...\n");
		return -1;
	}
	clock = mmc->clock;
	mmc_set_clock(mmc,0);

	err = mmc->switch_voltage(mmc,voltage);

	if(err!=0) {
		printf("mmc switch voltage failed...\n");
		return -1;
	}
	mdelay(5);
	mmc_set_clock(mmc,clock);
#endif /* CONFIG_SD30 */
	return 0;
}

int sd_init(struct mmc *mmc)
{
	int err;

	if (mmc->has_init) {
		if(!mmc->getcd(mmc)) {
			printf("SD: No card present\n");
			return -1;
		}
        return 0;
	}
	mmc->init(); /* rtk_sdmmc_init */

	err = mmc->getcd(mmc);
	if(!err) {
	    printf("SD: No card present\n");
	    return -2;
	}

	mmc_set_bus_width(mmc, 1);

	mmc_set_clock(mmc, 400000);

	// Reset the Card
	err = sd_go_idle(mmc);   //cmd0
	if (err) {
		printf("SD: cmd 0 fail");
	    return -3;
	}
	// The internal partition reset to user partition(0) at every CMD0
	mmc->part_num = 0;

	// Test for SD version 2
	err = sd_send_if_cond(mmc);   //cmd 8
	if (err) {
		printf("SD: cmd 8 fail");
	    return -4;
	}

	// Now try to get the SD card's operating condition
	err = sd_CR_send_op_cond(mmc);     //ACMD 41
	if (err) {
		printf("SD: acmd 41 fail");
	    return -5;
	}
#ifdef CONFIG_SD30
	if (!mmc_host_is_spi(mmc) && ((mmc->ocr & 0x41000000) == 0x41000000)) {
		err = sd_set_signal_voltage(mmc, MMC_SIGNAL_VOLTAGE_180);
		if (err) {
			printf("SD: switch voltage failed...\n");
	        return -6;
		}
	}
#endif /* CONFIG_SD30 */
	// If the command timed out, we check for an MMC card
	/*if (err == TIMEOUT) {
		err = mmc_send_op_cond(mmc);
		if (err) {
			printf("SD: Card did not respond to voltage select!\n");
			return UNUSABLE_ERR;
		}
	}*/

	err = sd_startup(mmc);
	if (err) {
		mmc->has_init = 0;
		DDDDGREEN("SD: init done but something wrong %d\n", err);
	}
	else {
		mmc->has_init = 1;
		DDDDGREEN("SD: init done, no error\n");
		DDDDGREEN("SD: capacity %ld sectors(0x%lx), (%ld MB)\n",  mmc->block_dev.lba, mmc->block_dev.lba, (mmc->block_dev.lba)/2048UL);
	}
	return err;
}

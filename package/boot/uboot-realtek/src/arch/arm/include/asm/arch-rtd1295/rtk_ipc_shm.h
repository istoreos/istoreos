#ifndef _RTK_IPC_SHM_H_
#define _RTK_IPC_SHM_H_

struct RTK119X_ipc_shm {
/*0C4*/	volatile unsigned int		sys_assign_serial;
/*0C8*/	volatile unsigned int		pov_boot_vd_std_ptr;
/*0CC*/	volatile unsigned int		pov_boot_av_info;
/*0D0*/	volatile unsigned int		audio_rpc_flag;
/*0D4*/	volatile unsigned int		suspend_mask;
/*0D8*/	volatile unsigned int		suspend_flag;
/*0DC*/ volatile unsigned int		vo_vsync_flag;
/*0E0*/	volatile unsigned int		audio_fw_entry_pt;
/*0E4*/	volatile unsigned int		power_saving_ptr;
/*0E8*/	volatile unsigned char	printk_buffer[24];
/*100*/	volatile unsigned int		ir_extended_tbl_pt;
/*104*/	volatile unsigned int		vo_int_sync;
/*108*/	volatile unsigned int		bt_wakeup_flag;//Bit31~24:magic key(0xEA), Bit23:high-active(1) low-active(0), Bit22~0:mask
/*10C*/	volatile unsigned int		ir_scancode_mask;
/*110*/	volatile unsigned int		ir_wakeup_scancode;
/*114*/	volatile unsigned int	    suspend_wakeup_flag;                /* [31-24] magic key(0xEA) [5] cec [4] timer [3] alarm [2] gpio [1] ir [0] lan , (0) disable (1) enable */
/*118*/	volatile unsigned int	    acpu_resume_state;                  /* [31-24] magic key(0xEA) [23-16] enum { NONE = 0, UNKNOW, IR, GPIO, LAN, ALARM, TIMER, CEC}  [15-0] ex GPIO Number */
/*11C*/	volatile unsigned int        gpio_wakeup_enable;                 /* [31-24] magic key(0xEA) [23-0] mapping to the number of iso gpio 0~23 */
/*120*/	volatile unsigned int        gpio_wakeup_activity;               /* [31-24] magic key(0xEA) [23-0] mapping to the number of iso gpio 0~23 , (0) low activity (1) high activity */
/*124*/	volatile unsigned int        gpio_output_change_enable;          /* [31-24] magic key(0xEA) [23-0] mapping to the number of iso gpio 0~23 */
/*128*/	volatile unsigned int        gpio_output_change_activity;        /* [31-24] magic key(0xEA) [23-0] mapping to the number of iso gpio 0~23 , (0) low activity (1) high activity AT SUSPEND TIME */
/*12C*/ volatile unsigned int        audio_reciprocal_timer_sec;         /* [31-24] magic key(0xEA) [23-0] audio reciprocal timer (sec) */
/*130*/ volatile unsigned int        u_boot_version_magic;
/*134*/ volatile unsigned int        u_boot_version_info;
/*138*/ volatile unsigned int        suspend_watchdog;                   /* [31-24] magic key(0xEA) [23] state (0) disable (1) enable [22] acpu response state [15-0] watch timeout (sec) */
/*13C*/ volatile unsigned int       xen_domu_boot_st;                    /* [31-24] magic key(0xEA) [23-20] version [19-16] Author (1) ACPU (2) SCPU [15-8] STATE [7-0] EXT */
/*140*/	volatile unsigned int		gpio_wakeup_enable2;				/* [31-24] magic key(0xEA) [10-0] mapping to the number of iso gpio 24~34 */
/*144*/	volatile unsigned int		gpio_wakeup_activity2;				/* [31-24] magic key(0xEA) [10-0] mapping to the number of iso gpio 24~34 , (0) low activity (1) high activity */
/*148*/	volatile unsigned int		gpio_output_change_enable2;			/* [31-24] magic key(0xEA) [10-0] mapping to the number of iso gpio 24~34 */
/*14C*/	volatile unsigned int		gpio_output_change_activity2;		/* [31-24] magic key(0xEA) [10-0] mapping to the number of iso gpio 24~34 , (0) low activity (1) high activity AT SUSPEND TIME */
};

struct RTK119X_ir_wake_up_key {
	unsigned int protocol;
	unsigned int ir_scancode_mask;
	unsigned int ir_wakeup_scancode;
	unsigned int ir_cus_mask;
	unsigned int ir_cus_code;
};

struct RTK119X_ipc_shm_ir {
	unsigned int RTK119X_ipc_shm_ir_magic;
	unsigned int dev_count;
	struct RTK119X_ir_wake_up_key key_tbl[5];
};

extern struct RTK119X_ipc_shm ipc_shm;
extern struct RTK119X_ipc_shm_ir ipc_ir;
extern int ipc_ir_set;

void set_shared_memory_ir_tbl(struct RTK119X_ipc_shm_ir *tbl_addr);
#endif // __RTK_IPC_SHM_H__

/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef RK_AVB_OPS_USER_H_
#define RK_AVB_OPS_USER_H_

#include <android_avb/avb_ops_user.h>
#include <android_avb/libavb_ab.h>

#ifdef __cplusplus
extern "C" {
#endif

/* rk used */
#define PERM_ATTR_DIGEST_SIZE 32
#define PERM_ATTR_TOTAL_SIZE  1052
#define VBOOT_KEY_HASH_SIZE   32
#define ANDROID_VBOOT_LOCK 0
#define ANDROID_VBOOT_UNLOCK 1
#define SLOT_NUM 2
#define CURR_SYSTEM_SLOT_SUFFIX "ab"
#define VBMETA_MAX_SIZE 65536
#define ROLLBACK_MAX_SIZE 20
#define LOCK_MASK 0x1
#define UNLOCK_DISABLE_MASK 0x2
#define VBOOT_STATE_SIZE    1000
#define PERM_ATTR_SUCCESS_FLAG 1
/* soc-v use the rsa2048 */
#define VBOOT_KEY_SIZE   256
#define RPMB_BASE_ADDR		(64*1024/256)
#define UBOOT_RB_INDEX_OFFSET 24
#define TRUST_RB_INDEX_OFFSET 28
#define ROCHCHIP_RSA_PARAMETER_SIZE 64

struct rk_pub_key {
	u_int32_t rsa_n[ROCHCHIP_RSA_PARAMETER_SIZE];
	u_int32_t rsa_e[ROCHCHIP_RSA_PARAMETER_SIZE];
	u_int32_t rsa_c[ROCHCHIP_RSA_PARAMETER_SIZE];
};

/**
 * Provided to fastboot to read how many slot in this system.
 *
 * @param slot_count  We use parameter slot_count to obtain
 *                    how many slots in the system.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_slot_count(char *slot_count);

/**
 * The android things supply many slots, their name like '_a', '_b'.
 * We can use this function to read current slot is '_a' or '_b'.
 *
 * @slot_suffixes  read value '_a' or '_b'.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_slot_suffixes(char *slot_suffixes);

/**
 * Use this function to set which slot boot first.
 *
 * @param slot_number set '0' or '1'
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_set_slot_active(unsigned int *slot_number);

/**
 * Get current slot: '_a' or '_b'.
 *
 * @param select_slot  obtain current slot.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_get_current_slot(char *select_slot);

/**
 * Append current slot to given partition name
 *
 * @param part_name	partition name
 * @param slot		given slot suffix, auto append current slot if NULL
 * @param new_name	partition name with slot suffix appended
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_append_part_slot(const char *part_name, char *new_name);

/**
 * The android things defines permanent attributes to
 * store PSK_public, product id. We can use this function
 * to read them.
 *
 * @param attributes  PSK_public, product id....
 *
 * @param size        The size of attributes.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_permanent_attributes(uint8_t *attributes, uint32_t size);

/**
 * The android things defines permanent attributes to
 * store PSK_public, product id. We can use this function
 * to write them.
 *
 * @param attributes  PSK_public, product id....
 *
 * @param size        The size of attributes.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_permanent_attributes(uint8_t *attributes, uint32_t size);

/**
 * The funtion can be use to read the device state to judge
 * whether the device can be flash.
 *
 * @param flash_lock_state  A flag indicate the device flash state.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_flash_lock_state(uint8_t *flash_lock_state);

/**
 * The function is provided to write device flash state.
 *
 * @param flash_lock_state   A flag indicate the device flash state.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_flash_lock_state(uint8_t flash_lock_state);

/**
 * The android things use the flag of lock state to indicate
 * whether the device can be booted when verified error.
 *
 * @param lock_state  A flag indicate the device lock state.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_lock_state(uint8_t *lock_state);

/**
 * The android things use the flag of lock state to indicate
 * whether the device can be booted when verified error.
 *
 * @param lock_state   A flag indicate the device lock state.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_lock_state(uint8_t lock_state);

/**
 * The android things uses fastboot to flash the permanent attributes.
 * And if them were written, there must have a flag to indicate.
 *
 * @param flag   indicate the permanent attributes have been written
 *               or not.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_perm_attr_flag(uint8_t *flag);

/**
 * The android things uses fastboot to flash the permanent attributes.
 * And if them were written, there must have a flag to indicate.
 *
 * @param flag   We can call this function to write the flag '1'
 *               to indicate the permanent attributes has been
 *               written.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_perm_attr_flag(uint8_t flag);

/**
 * The android things require the soc-v key hash to be flashed
 * using the fastboot. So the function can be used in fastboot
 * to flash the key hash.
 *
 * @param buf    The vboot key hash data.
 *
 * @param length The length of key hash.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_vbootkey_hash(uint8_t *buf, uint8_t length);

/**
 * The android things require the soc-v key hash to be flashed
 * using the fastboot. So the function can be used in fastboot
 * to flash the key hash.
 *
 * @param buf    The vboot key hash data.
 *
 * @param length The length of key hash.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_vbootkey_hash(uint8_t *buf, uint8_t length);

/**
 * U-boot close the optee client when start kernel
 * to prevent the optee client being invoking by other
 * program.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_close_optee_client(void);

/**
 * read the permanent attributes hash.
 *
 * @param buf    The permanent attributes hash data.
 *
 * @param length The length of permanent attributes hash.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_read_attribute_hash(uint8_t *buf, uint8_t length);

/**
 * Write the permanent attributes hash.
 *
 * @param buf    The permanent attributes hash data.
 *
 * @param length The length of permanent attributes hash.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_write_attribute_hash(uint8_t *buf, uint8_t length);

/**
 * Get the avb vboot state
 *
 * @param buf    store the vboot state.
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
void rk_avb_get_at_vboot_state(char *buf);

/**
 * Get ab information from misc partition
 *
 * @param ab_data    the struct of ab information
 *
 * @return 0 if the command succeeded, -1 if it failed
 */
int rk_avb_get_ab_info(AvbABData* ab_data);

/**
 * Get the information whether the partition has slot
 *
 * @param the partition name
 *
 * @return 0 if the partition has slot, -1 if not
 */
int rk_avb_get_part_has_slot_info(const char *base_name);

AvbABFlowResult rk_avb_ab_slot_select(AvbABOps* ab_ops,char select_slot[]);

/**
 * authenticated unlock
 *
 * @param buffer: AvbAtxUnlockCredential
 *
 * @param out_is_trusted: true or false
 *
 * @return 0 if authenticated unlock OK, -1 if not
 */
int rk_auth_unlock(void *buffer, char *out_is_trusted);

/**
 * generate unlock challenge
 *
 * @param buffer: AvbAtxUnlockChallenge
 *
 * @param challenge_len: Challenge length
 *
 * @param out_is_trusted: true or false
 *
 * @return 0 if generate unlock challenge OK, -1 if not
 */
int rk_generate_unlock_challenge(void *buffer, uint32_t *challenge_len);

/**
 * Get last boot slot
 *
 * @return 0 is slot A; 1 is slot B; -1 is error
 */
int rk_get_lastboot(void);

/**
 * Get permanent attribute certificate
 *
 * @param cer: certificate data
 *
 * @param size: certificate size
 */
int rk_avb_get_perm_attr_cer(uint8_t *cer, uint32_t size);

/**
 * Set permanent attribute certificate
 *
 * @param cer: certificate data
 *
 * @param size: certificate size
 */
int rk_avb_set_perm_attr_cer(uint8_t *cer, uint32_t size);

/**
 * Get public key
 *
 * @param pub_key: public key data
 */
int rk_avb_get_pub_key(struct rk_pub_key *pub_key);

/**
 * init ab metadata
 */
int rk_avb_init_ab_metadata(void);

/**
 * rockchip avb commands
 */
int rk_avb_write_perm_attr(uint16_t id, void *pbuf, uint16_t size);
int rk_avb_read_perm_attr(uint16_t id, void *pbuf, uint16_t size);

/**
 * Do the device have boot slot
 */
bool rk_avb_ab_have_bootable_slot(void);

/**
 * update rollback index
 */
int rk_avb_update_stored_rollback_indexes_for_slot(AvbOps* ops, AvbSlotVerifyData* slot_data);

#ifdef __cplusplus
}
#endif

#endif /* RK_AVB_OPS_USER_H_ */

/*
 * This is from the Android Project,
 * Repository: https://android.googlesource.com/platform/bootable/recovery/
 * File: bootloader_message/include/bootloader_message/bootloader_message.h
 * Commit: 8b309f6970ab3b7c53cc529c51a2cb44e1c7a7e1
 *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __ANDROID_BOOTLOADER_MESSAGE_H
#define __ANDROID_BOOTLOADER_MESSAGE_H

/* compiler.h defines the types that otherwise are included from stdint.h and
 * stddef.h
 */
#include <compiler.h>

/* Spaces used by misc partition are as below:
 * 0   - 2K     Bootloader Message
 * 2K  - 16K    Used by Vendor's bootloader (the 2K - 4K range may be optionally used
 *              as bootloader_message_ab struct)
 * 16K - 32K    Used by uncrypt and recovery to store wipe_package for A/B devices
 * 32K - 64K    System space, used for miscellaneous AOSP features (virtual A/B metadata).
 * Note that these offsets are admitted by bootloader,recovery and uncrypt, so they
 * are not configurable without changing all of them.
 */
static const size_t ANDROID_BOOTLOADER_MESSAGE_OFFSET_IN_MISC = 0;
static const size_t ANDROID_WIPE_PACKAGE_OFFSET_IN_MISC = 16 * 1024;
static const size_t ANDROID_VIRTUAL_AB_METADATA_OFFSET_IN_MISC = 32 * 1024;

/* Bootloader Message (2-KiB)
 *
 * This structure describes the content of a block in flash
 * that is used for recovery and the bootloader to talk to
 * each other.
 *
 * The command field is updated by linux when it wants to
 * reboot into recovery or to update radio or bootloader firmware.
 * It is also updated by the bootloader when firmware update
 * is complete (to boot into recovery for any final cleanup)
 *
 * The status field is written by the bootloader after the
 * completion of an "update-radio" or "update-hboot" command.
 *
 * The recovery field is only written by linux and used
 * for the system to send a message to recovery or the
 * other way around.
 *
 * The stage field is written by packages which restart themselves
 * multiple times, so that the UI can reflect which invocation of the
 * package it is.  If the value is of the format "#/#" (eg, "1/3"),
 * the UI will add a simple indicator of that status.
 *
 * We used to have slot_suffix field for A/B boot control metadata in
 * this struct, which gets unintentionally cleared by recovery or
 * uncrypt. Move it into struct bootloader_message_ab to avoid the
 * issue.
 */
struct android_bootloader_message {
    char command[32];
    char status[32];
    char recovery[768];

    /* The 'recovery' field used to be 1024 bytes.  It has only ever
     * been used to store the recovery command line, so 768 bytes
     * should be plenty.  We carve off the last 256 bytes to store the
     * stage string (for multistage packages) and possible future
     * expansion. */
    char stage[32];

    /* The 'reserved' field used to be 224 bytes when it was initially
     * carved off from the 1024-byte recovery field. Bump it up to
     * 1184-byte so that the entire bootloader_message struct rounds up
     * to 2048-byte. */
    char reserved[1184];
};

/**
 * We must be cautious when changing the bootloader_message struct size,
 * because A/B-specific fields may end up with different offsets.
 */
#if (__STDC_VERSION__ >= 201112L) || defined(__cplusplus)
static_assert(sizeof(struct android_bootloader_message) == 2048,
              "struct bootloader_message size changes, which may break A/B devices");
#endif

/**
 * The A/B-specific bootloader message structure (4-KiB).
 *
 * We separate A/B boot control metadata from the regular bootloader
 * message struct and keep it here. Everything that's A/B-specific
 * stays after struct bootloader_message, which should be managed by
 * the A/B-bootloader or boot control HAL.
 *
 * The slot_suffix field is used for A/B implementations where the
 * bootloader does not set the androidboot.ro.boot.slot_suffix kernel
 * commandline parameter. This is used by fs_mgr to mount /system and
 * other partitions with the slotselect flag set in fstab. A/B
 * implementations are free to use all 32 bytes and may store private
 * data past the first NUL-byte in this field. It is encouraged, but
 * not mandatory, to use 'struct bootloader_control' described below.
 */
struct android_bootloader_message_ab {
    struct android_bootloader_message message;
    char slot_suffix[32];

    /* Round up the entire struct to 4096-byte. */
    char reserved[2016];
};

/**
 * Be cautious about the struct size change, in case we put anything post
 * bootloader_message_ab struct (b/29159185).
 */
#if (__STDC_VERSION__ >= 201112L) || defined(__cplusplus)
static_assert(sizeof(struct android_bootloader_message_ab) == 4096,
              "struct bootloader_message_ab size changes");
#endif

#define ANDROID_BOOT_CTRL_MAGIC   0x42414342 /* Bootloader Control AB */
#define ANDROID_BOOT_CTRL_VERSION 1

struct android_slot_metadata {
    /* Slot priority with 15 meaning highest priority, 1 lowest
     * priority and 0 the slot is unbootable. */
    uint8_t priority : 4;
    /* Number of times left attempting to boot this slot. */
    uint8_t tries_remaining : 3;
    /* 1 if this slot has booted successfully, 0 otherwise. */
    uint8_t successful_boot : 1;
    /* 1 if this slot is corrupted from a dm-verity corruption, 0 */
    /* otherwise. */
    uint8_t verity_corrupted : 1;
    /* Reserved for further use. */
    uint8_t reserved : 7;
} __attribute__((packed));

/* Bootloader Control AB
 *
 * This struct can be used to manage A/B metadata. It is designed to
 * be put in the 'slot_suffix' field of the 'bootloader_message'
 * structure described above. It is encouraged to use the
 * 'bootloader_control' structure to store the A/B metadata, but not
 * mandatory.
 */
struct android_bootloader_control {
    /* NUL terminated active slot suffix. */
    char slot_suffix[4];
    /* Bootloader Control AB magic number (see BOOT_CTRL_MAGIC). */
    uint32_t magic;
    /* Version of struct being used (see BOOT_CTRL_VERSION). */
    uint8_t version;
    /* Number of slots being managed. */
    uint8_t nb_slot : 3;
    /* Number of times left attempting to boot recovery. */
    uint8_t recovery_tries_remaining : 3;
    /* Ensure 4-bytes alignment for slot_info field. */
    uint8_t reserved0[2];
    /* Per-slot information.  Up to 4 slots. */
    struct android_slot_metadata slot_info[4];
    /* Reserved for further use. */
    uint8_t reserved1[8];
    /* CRC32 of all 28 bytes preceding this field (little endian
     * format). */
    uint32_t crc32_le;
} __attribute__((packed));

#if (__STDC_VERSION__ >= 201112L) || defined(__cplusplus)
static_assert(sizeof(struct android_bootloader_control) ==
              sizeof(((struct android_bootloader_message_ab *)0)->slot_suffix),
              "struct bootloader_control has wrong size");
#endif

#endif  /* __ANDROID_BOOTLOADER_MESSAGE_H */

/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* Based on GP TEE Internal API Specification Version 0.11 */
#ifndef TEE_API_TYPES_H
#define TEE_API_TYPES_H

#include <optee_include/tee_base_types.h>
#include <optee_include/tee_api_defines.h>


/*
 * Common Definitions
 */

typedef uint32_t TEE_Result;

typedef struct {
	uint32_t timeLow;
	uint16_t timeMid;
	uint16_t timeHiAndVersion;
	uint8_t clockSeqAndNode[8];
} TEE_UUID;

/*
 * The TEE_Identity structure defines the full identity of a Client:
 * - login is one of the TEE_LOGIN_XXX constants
 * - uuid contains the client UUID or Nil if not applicable
 */
typedef struct {
	uint32_t login;
	TEE_UUID uuid;
} TEE_Identity;

/*
 * This union describes one parameter passed by the Trusted Core Framework
 * to the entry points TA_OpenSessionEntryPoint or
 * TA_InvokeCommandEntryPoint or by the TA to the functions
 * TEE_OpenTASession or TEE_InvokeTACommand.
 *
 * Which of the field value or memref to select is determined by the
 * parameter type specified in the argument paramTypes passed to the entry
 * point.
*/
typedef union {
	struct {
		void *buffer;
		uint32_t size;
	} memref;
	struct {
		uint32_t a;
		uint32_t b;
	} value;
} TEE_Param;

/*
 * The type of opaque handles on TA Session. These handles are returned by
 * the function TEE_OpenTASession.
 */
typedef struct __TEE_TASessionHandle *TEE_TASessionHandle;

/*
 * The type of opaque handles on property sets or enumerators. These
 * handles are either one of the pseudo handles TEE_PROPSET_XXX or are
 * returned by the function TEE_AllocatePropertyEnumerator.
*/
typedef struct __TEE_PropSetHandle *TEE_PropSetHandle;

typedef struct __TEE_ObjectHandle *TEE_ObjectHandle;
typedef struct __TEE_ObjectEnumHandle *TEE_ObjectEnumHandle;
typedef struct __TEE_OperationHandle *TEE_OperationHandle;

/*
 * Storage Definitions
 */

typedef uint32_t TEE_ObjectType;

typedef struct {
	uint32_t objectType;
	uint32_t keySize;
	uint32_t maxKeySize;
	uint32_t objectUsage;
	uint32_t dataSize;
	uint32_t dataPosition;
	uint32_t handleFlags;
} TEE_ObjectInfo;

typedef enum {
	TEE_DATA_SEEK_SET = 0,
	TEE_DATA_SEEK_CUR = 1,
	TEE_DATA_SEEK_END = 2
} TEE_Whence;

typedef struct {
	uint32_t attributeID;
	union {
		struct {
			void *buffer;
			uint32_t length;
		} ref;
		struct {
			uint32_t a, b;
		} value;
	} content;
} TEE_Attribute;

/* Cryptographic Operations API */

typedef enum {
	TEE_MODE_ENCRYPT = 0,
	TEE_MODE_DECRYPT = 1,
	TEE_MODE_SIGN = 2,
	TEE_MODE_VERIFY = 3,
	TEE_MODE_MAC = 4,
	TEE_MODE_DIGEST = 5,
	TEE_MODE_DERIVE = 6
} TEE_OperationMode;

typedef struct {
	uint32_t algorithm;
	uint32_t operationClass;
	uint32_t mode;
	uint32_t digestLength;
	uint32_t maxKeySize;
	uint32_t keySize;
	uint32_t requiredKeyUsage;
	uint32_t handleState;
} TEE_OperationInfo;

typedef struct {
	uint32_t keySize;
	uint32_t requiredKeyUsage;
} TEE_OperationInfoKey;

typedef struct {
	uint32_t algorithm;
	uint32_t operationClass;
	uint32_t mode;
	uint32_t digestLength;
	uint32_t maxKeySize;
	uint32_t handleState;
	uint32_t operationState;
	uint32_t numberOfKeys;
	TEE_OperationInfoKey keyInformation[];
} TEE_OperationInfoMultiple;

/* Time & Date API */

typedef struct {
	uint32_t seconds;
	uint32_t millis;
} TEE_Time;

/* TEE Arithmetical APIs */

typedef uint32_t TEE_BigInt;

typedef uint32_t TEE_BigIntFMM;

typedef uint32_t TEE_BigIntFMMContext;

/* Tee Secure Element APIs */

typedef struct __TEE_SEServiceHandle *TEE_SEServiceHandle;
typedef struct __TEE_SEReaderHandle *TEE_SEReaderHandle;
typedef struct __TEE_SESessionHandle *TEE_SESessionHandle;
typedef struct __TEE_SEChannelHandle *TEE_SEChannelHandle;

typedef struct {
	bool sePresent;
	bool teeOnly;
	bool selectResponseEnable;
} TEE_SEReaderProperties;

typedef struct {
	uint8_t *buffer;
	size_t bufferLen;
} TEE_SEAID;

/* Other definitions */
typedef uint32_t TEE_ErrorOrigin;
typedef void *TEE_Session;

#define TEE_MEM_INPUT   0x00000001
#define TEE_MEM_OUTPUT  0x00000002

#define TEE_MEMREF_0_USED  0x00000001
#define TEE_MEMREF_1_USED  0x00000002
#define TEE_MEMREF_2_USED  0x00000004
#define TEE_MEMREF_3_USED  0x00000008

#define TEE_SE_READER_NAME_MAX	20

#endif /* TEE_API_TYPES_H */

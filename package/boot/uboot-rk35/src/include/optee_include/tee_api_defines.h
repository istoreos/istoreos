/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* Based on GP TEE Internal Core API Specification Version 1.1 */
#ifndef TEE_API_DEFINES_H
#define TEE_API_DEFINES_H

#include <optee_include/tee_base_types.h>

#define TEE_INT_CORE_API_SPEC_VERSION     0x0000000A

#define TEE_HANDLE_NULL                   0

#define TEE_TIMEOUT_INFINITE              0xFFFFFFFF

/* API Error Codes */
#define TEE_SUCCESS                       0x00000000
#define TEE_ERROR_CORRUPT_OBJECT          0xF0100001
#define TEE_ERROR_CORRUPT_OBJECT_2        0xF0100002
#define TEE_ERROR_STORAGE_NOT_AVAILABLE   0xF0100003
#define TEE_ERROR_STORAGE_NOT_AVAILABLE_2 0xF0100004
#define TEE_ERROR_GENERIC                 0xFFFF0000
#define TEE_ERROR_ACCESS_DENIED           0xFFFF0001
#define TEE_ERROR_CANCEL                  0xFFFF0002
#define TEE_ERROR_ACCESS_CONFLICT         0xFFFF0003
#define TEE_ERROR_EXCESS_DATA             0xFFFF0004
#define TEE_ERROR_BAD_FORMAT              0xFFFF0005
#define TEE_ERROR_BAD_PARAMETERS          0xFFFF0006
#define TEE_ERROR_BAD_STATE               0xFFFF0007
#define TEE_ERROR_ITEM_NOT_FOUND          0xFFFF0008
#define TEE_ERROR_NOT_IMPLEMENTED         0xFFFF0009
#define TEE_ERROR_NOT_SUPPORTED           0xFFFF000A
#define TEE_ERROR_NO_DATA                 0xFFFF000B
#define TEE_ERROR_OUT_OF_MEMORY           0xFFFF000C
#define TEE_ERROR_BUSY                    0xFFFF000D
#define TEE_ERROR_COMMUNICATION           0xFFFF000E
#define TEE_ERROR_SECURITY                0xFFFF000F
#define TEE_ERROR_SHORT_BUFFER            0xFFFF0010
#define TEE_ERROR_EXTERNAL_CANCEL         0xFFFF0011
#define TEE_ERROR_OVERFLOW                0xFFFF300F
#define TEE_ERROR_TARGET_DEAD             0xFFFF3024
#define TEE_ERROR_STORAGE_NO_SPACE        0xFFFF3041
#define TEE_ERROR_MAC_INVALID             0xFFFF3071
#define TEE_ERROR_SIGNATURE_INVALID       0xFFFF3072
#define TEE_ERROR_TIME_NOT_SET            0xFFFF5000
#define TEE_ERROR_TIME_NEEDS_RESET        0xFFFF5001

/*
 * Proprietary error codes.
 * All proprietary error codes should use the 0xF57E prefix.
 */
#define TEE_ERROR_SYSTEM_BUSY           0xF57E0000
#define TEE_ERROR_FILE_NOT_FOUND        0xF57E0010

/* Parameter Type Constants */
#define TEE_PARAM_TYPE_NONE             0
#define TEE_PARAM_TYPE_VALUE_INPUT      1
#define TEE_PARAM_TYPE_VALUE_OUTPUT     2
#define TEE_PARAM_TYPE_VALUE_INOUT      3
#define TEE_PARAM_TYPE_MEMREF_INPUT     5
#define TEE_PARAM_TYPE_MEMREF_OUTPUT    6
#define TEE_PARAM_TYPE_MEMREF_INOUT     7

/* Login Type Constants */
#define TEE_LOGIN_PUBLIC                0x00000000
#define TEE_LOGIN_USER                  0x00000001
#define TEE_LOGIN_GROUP                 0x00000002
#define TEE_LOGIN_APPLICATION           0x00000004
#define TEE_LOGIN_APPLICATION_USER      0x00000005
#define TEE_LOGIN_APPLICATION_GROUP     0x00000006
#define TEE_LOGIN_TRUSTED_APP           0xF0000000

/* Origin Code Constants */
#define TEE_ORIGIN_API                  0x00000001
#define TEE_ORIGIN_COMMS                0x00000002
#define TEE_ORIGIN_TEE                  0x00000003
#define TEE_ORIGIN_TRUSTED_APP          0x00000004

/* Property Sets pseudo handles */
#define TEE_PROPSET_TEE_IMPLEMENTATION  ((TEE_PropSetHandle)0xFFFFFFFD)
#define TEE_PROPSET_CURRENT_CLIENT      ((TEE_PropSetHandle)0xFFFFFFFE)
#define TEE_PROPSET_CURRENT_TA          ((TEE_PropSetHandle)0xFFFFFFFF)

/* Memory Access Rights Constants */
#define TEE_MEMORY_ACCESS_READ             0x00000001
#define TEE_MEMORY_ACCESS_WRITE            0x00000002
#define TEE_MEMORY_ACCESS_ANY_OWNER        0x00000004

/* Other constants */
#define TEE_STORAGE_PRIVATE                0x00000001

#define TEE_DATA_FLAG_ACCESS_READ          0x00000001
#define TEE_DATA_FLAG_ACCESS_WRITE         0x00000002
#define TEE_DATA_FLAG_ACCESS_WRITE_META    0x00000004
#define TEE_DATA_FLAG_SHARE_READ           0x00000010
#define TEE_DATA_FLAG_SHARE_WRITE          0x00000020
#define TEE_DATA_FLAG_EXCLUSIVE            0x00000400
#define TEE_DATA_MAX_POSITION              0xFFFFFFFF
#define TEE_OBJECT_ID_MAX_LEN              64
#define TEE_USAGE_EXTRACTABLE              0x00000001
#define TEE_USAGE_ENCRYPT                  0x00000002
#define TEE_USAGE_DECRYPT                  0x00000004
#define TEE_USAGE_MAC                      0x00000008
#define TEE_USAGE_SIGN                     0x00000010
#define TEE_USAGE_VERIFY                   0x00000020
#define TEE_USAGE_DERIVE                   0x00000040
#define TEE_HANDLE_FLAG_PERSISTENT         0x00010000
#define TEE_HANDLE_FLAG_INITIALIZED        0x00020000
#define TEE_HANDLE_FLAG_KEY_SET            0x00040000
#define TEE_HANDLE_FLAG_EXPECT_TWO_KEYS    0x00080000
#define TEE_OPERATION_CIPHER               1
#define TEE_OPERATION_MAC                  3
#define TEE_OPERATION_AE                   4
#define TEE_OPERATION_DIGEST               5
#define TEE_OPERATION_ASYMMETRIC_CIPHER    6
#define TEE_OPERATION_ASYMMETRIC_SIGNATURE 7
#define TEE_OPERATION_KEY_DERIVATION       8
#define TEE_OPERATION_STATE_INITIAL        0x00000000
#define TEE_OPERATION_STATE_ACTIVE         0x00000001

/* Algorithm Identifiers */
#define TEE_ALG_AES_ECB_NOPAD                   0x10000010
#define TEE_ALG_AES_CBC_NOPAD                   0x10000110
#define TEE_ALG_AES_CTR                         0x10000210
#define TEE_ALG_AES_CTS                         0x10000310
#define TEE_ALG_AES_XTS                         0x10000410
#define TEE_ALG_AES_CBC_MAC_NOPAD               0x30000110
#define TEE_ALG_AES_CBC_MAC_PKCS5               0x30000510
#define TEE_ALG_AES_CMAC                        0x30000610
#define TEE_ALG_AES_CCM                         0x40000710
#define TEE_ALG_AES_GCM                         0x40000810
#define TEE_ALG_DES_ECB_NOPAD                   0x10000011
#define TEE_ALG_DES_CBC_NOPAD                   0x10000111
#define TEE_ALG_DES_CBC_MAC_NOPAD               0x30000111
#define TEE_ALG_DES_CBC_MAC_PKCS5               0x30000511
#define TEE_ALG_DES3_ECB_NOPAD                  0x10000013
#define TEE_ALG_DES3_CBC_NOPAD                  0x10000113
#define TEE_ALG_DES3_CBC_MAC_NOPAD              0x30000113
#define TEE_ALG_DES3_CBC_MAC_PKCS5              0x30000513
#define TEE_ALG_RSASSA_PKCS1_V1_5_MD5           0x70001830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA1          0x70002830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA224        0x70003830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA256        0x70004830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA384        0x70005830
#define TEE_ALG_RSASSA_PKCS1_V1_5_SHA512        0x70006830
#define TEE_ALG_RSASSA_PKCS1_V1_5_MD5SHA1       0x7000F830
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1      0x70212930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA224    0x70313930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256    0x70414930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA384    0x70515930
#define TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA512    0x70616930
#define TEE_ALG_RSAES_PKCS1_V1_5                0x60000130
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1      0x60210230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA224    0x60310230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256    0x60410230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA384    0x60510230
#define TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA512    0x60610230
#define TEE_ALG_RSA_NOPAD                       0x60000030
#define TEE_ALG_DSA_SHA1                        0x70002131
#define TEE_ALG_DSA_SHA224                      0x70003131
#define TEE_ALG_DSA_SHA256                      0x70004131
#define TEE_ALG_DH_DERIVE_SHARED_SECRET         0x80000032
#define TEE_ALG_MD5                             0x50000001
#define TEE_ALG_SHA1                            0x50000002
#define TEE_ALG_SHA224                          0x50000003
#define TEE_ALG_SHA256                          0x50000004
#define TEE_ALG_SHA384                          0x50000005
#define TEE_ALG_SHA512                          0x50000006
#define TEE_ALG_MD5SHA1                         0x5000000F
#define TEE_ALG_HMAC_MD5                        0x30000001
#define TEE_ALG_HMAC_SHA1                       0x30000002
#define TEE_ALG_HMAC_SHA224                     0x30000003
#define TEE_ALG_HMAC_SHA256                     0x30000004
#define TEE_ALG_HMAC_SHA384                     0x30000005
#define TEE_ALG_HMAC_SHA512                     0x30000006
#define TEE_ALG_ECDSA_P192                      0x70001042
#define TEE_ALG_ECDSA_P224                      0x70002042
#define TEE_ALG_ECDSA_P256                      0x70003042
#define TEE_ALG_ECDSA_P384                      0x70004042
#define TEE_ALG_ECDSA_P521                      0x70005042
#define TEE_ALG_ECDH_P192                       0x80001042
#define TEE_ALG_ECDH_P224                       0x80002042
#define TEE_ALG_ECDH_P256                       0x80003042
#define TEE_ALG_ECDH_P384                       0x80004042
#define TEE_ALG_ECDH_P521                       0x80005042

/* Object Types */

#define TEE_TYPE_AES                        0xA0000010
#define TEE_TYPE_DES                        0xA0000011
#define TEE_TYPE_DES3                       0xA0000013
#define TEE_TYPE_HMAC_MD5                   0xA0000001
#define TEE_TYPE_HMAC_SHA1                  0xA0000002
#define TEE_TYPE_HMAC_SHA224                0xA0000003
#define TEE_TYPE_HMAC_SHA256                0xA0000004
#define TEE_TYPE_HMAC_SHA384                0xA0000005
#define TEE_TYPE_HMAC_SHA512                0xA0000006
#define TEE_TYPE_RSA_PUBLIC_KEY             0xA0000030
#define TEE_TYPE_RSA_KEYPAIR                0xA1000030
#define TEE_TYPE_DSA_PUBLIC_KEY             0xA0000031
#define TEE_TYPE_DSA_KEYPAIR                0xA1000031
#define TEE_TYPE_DH_KEYPAIR                 0xA1000032
#define TEE_TYPE_ECDSA_PUBLIC_KEY           0xA0000041
#define TEE_TYPE_ECDSA_KEYPAIR              0xA1000041
#define TEE_TYPE_ECDH_PUBLIC_KEY            0xA0000042
#define TEE_TYPE_ECDH_KEYPAIR               0xA1000042
#define TEE_TYPE_GENERIC_SECRET             0xA0000000
#define TEE_TYPE_CORRUPTED_OBJECT           0xA00000BE
#define TEE_TYPE_DATA                       0xA00000BF

/* List of Object or Operation Attributes */

#define TEE_ATTR_SECRET_VALUE               0xC0000000
#define TEE_ATTR_RSA_MODULUS                0xD0000130
#define TEE_ATTR_RSA_PUBLIC_EXPONENT        0xD0000230
#define TEE_ATTR_RSA_PRIVATE_EXPONENT       0xC0000330
#define TEE_ATTR_RSA_PRIME1                 0xC0000430
#define TEE_ATTR_RSA_PRIME2                 0xC0000530
#define TEE_ATTR_RSA_EXPONENT1              0xC0000630
#define TEE_ATTR_RSA_EXPONENT2              0xC0000730
#define TEE_ATTR_RSA_COEFFICIENT            0xC0000830
#define TEE_ATTR_DSA_PRIME                  0xD0001031
#define TEE_ATTR_DSA_SUBPRIME               0xD0001131
#define TEE_ATTR_DSA_BASE                   0xD0001231
#define TEE_ATTR_DSA_PUBLIC_VALUE           0xD0000131
#define TEE_ATTR_DSA_PRIVATE_VALUE          0xC0000231
#define TEE_ATTR_DH_PRIME                   0xD0001032
#define TEE_ATTR_DH_SUBPRIME                0xD0001132
#define TEE_ATTR_DH_BASE                    0xD0001232
#define TEE_ATTR_DH_X_BITS                  0xF0001332
#define TEE_ATTR_DH_PUBLIC_VALUE            0xD0000132
#define TEE_ATTR_DH_PRIVATE_VALUE           0xC0000232
#define TEE_ATTR_RSA_OAEP_LABEL             0xD0000930
#define TEE_ATTR_RSA_PSS_SALT_LENGTH        0xF0000A30
#define TEE_ATTR_ECC_PUBLIC_VALUE_X         0xD0000141
#define TEE_ATTR_ECC_PUBLIC_VALUE_Y         0xD0000241
#define TEE_ATTR_ECC_PRIVATE_VALUE          0xC0000341
#define TEE_ATTR_ECC_CURVE                  0xF0000441

#define TEE_ATTR_BIT_PROTECTED		(1 << 28)
#define TEE_ATTR_BIT_VALUE		(1 << 29)

/* Panicked Functions Identification */
/* TA Interface */
#define TEE_PANIC_ID_TA_CLOSESESSIONENTRYPOINT      0x00000101
#define TEE_PANIC_ID_TA_CREATEENTRYPOINT            0x00000102
#define TEE_PANIC_ID_TA_DESTROYENTRYPOINT           0x00000103
#define TEE_PANIC_ID_TA_INVOKECOMMANDENTRYPOINT     0x00000104
#define TEE_PANIC_ID_TA_OPENSESSIONENTRYPOINT       0x00000105
/* Property Access */
#define TEE_PANIC_ID_TEE_ALLOCATEPROPERTYENUMERATOR 0x00000201
#define TEE_PANIC_ID_TEE_FREEPROPERTYENUMERATOR     0x00000202
#define TEE_PANIC_ID_TEE_GETNEXTPROPERTY            0x00000203
#define TEE_PANIC_ID_TEE_GETPROPERTYASBINARYBLOCK   0x00000204
#define TEE_PANIC_ID_TEE_GETPROPERTYASBOOL          0x00000205
#define TEE_PANIC_ID_TEE_GETPROPERTYASIDENTITY      0x00000206
#define TEE_PANIC_ID_TEE_GETPROPERTYASSTRING        0x00000207
#define TEE_PANIC_ID_TEE_GETPROPERTYASU32           0x00000208
#define TEE_PANIC_ID_TEE_GETPROPERTYASUUID          0x00000209
#define TEE_PANIC_ID_TEE_GETPROPERTYNAME            0x0000020A
#define TEE_PANIC_ID_TEE_RESETPROPERTYENUMERATOR    0x0000020B
#define TEE_PANIC_ID_TEE_STARTPROPERTYENUMERATOR    0x0000020C
/* Panic Function */
#define TEE_PANIC_ID_TEE_PANIC                      0x00000301
/* Internal Client API */
#define TEE_PANIC_ID_TEE_CLOSETASESSION             0x00000401
#define TEE_PANIC_ID_TEE_INVOKETACOMMAND            0x00000402
#define TEE_PANIC_ID_TEE_OPENTASESSION              0x00000403
/* Cancellation */
#define TEE_PANIC_ID_TEE_GETCANCELLATIONFLAG        0x00000501
#define TEE_PANIC_ID_TEE_MASKCANCELLATION           0x00000502
#define TEE_PANIC_ID_TEE_UNMASKCANCELLATION         0x00000503
/* Memory Management */
#define TEE_PANIC_ID_TEE_CHECKMEMORYACCESSRIGHTS    0x00000601
#define TEE_PANIC_ID_TEE_FREE                       0x00000602
#define TEE_PANIC_ID_TEE_GETINSTANCEDATA            0x00000603
#define TEE_PANIC_ID_TEE_MALLOC                     0x00000604
#define TEE_PANIC_ID_TEE_MEMCOMPARE                 0x00000605
#define TEE_PANIC_ID_TEE_MEMFILL                    0x00000606
#define TEE_PANIC_ID_TEE_MEMMOVE                    0x00000607
#define TEE_PANIC_ID_TEE_REALLOC                    0x00000608
#define TEE_PANIC_ID_TEE_SETINSTANCEDATA            0x00000609
/* Generic Object */
#define TEE_PANIC_ID_TEE_CLOSEOBJECT                0x00000701
#define TEE_PANIC_ID_TEE_GETOBJECTBUFFERATTRIBUTE   0x00000702
/* deprecated */
#define TEE_PANIC_ID_TEE_GETOBJECTINFO              0x00000703
#define TEE_PANIC_ID_TEE_GETOBJECTVALUEATTRIBUTE    0x00000704
/* deprecated */
#define TEE_PANIC_ID_TEE_RESTRICTOBJECTUSAGE        0x00000705
#define TEE_PANIC_ID_TEE_GETOBJECTINFO1             0x00000706
#define TEE_PANIC_ID_TEE_RESTRICTOBJECTUSAGE1       0x00000707
/* Transient Object */
#define TEE_PANIC_ID_TEE_ALLOCATETRANSIENTOBJECT    0x00000801
/* deprecated */
#define TEE_PANIC_ID_TEE_COPYOBJECTATTRIBUTES       0x00000802
#define TEE_PANIC_ID_TEE_FREETRANSIENTOBJECT        0x00000803
#define TEE_PANIC_ID_TEE_GENERATEKEY                0x00000804
#define TEE_PANIC_ID_TEE_INITREFATTRIBUTE           0x00000805
#define TEE_PANIC_ID_TEE_INITVALUEATTRIBUTE         0x00000806
#define TEE_PANIC_ID_TEE_POPULATETRANSIENTOBJECT    0x00000807
#define TEE_PANIC_ID_TEE_RESETTRANSIENTOBJECT       0x00000808
#define TEE_PANIC_ID_TEE_COPYOBJECTATTRIBUTES1      0x00000809
/* Persistent Object */
/* deprecated */
#define TEE_PANIC_ID_TEE_CLOSEANDDELETEPERSISTENTOBJECT  0x00000901
#define TEE_PANIC_ID_TEE_CREATEPERSISTENTOBJECT          0x00000902
#define TEE_PANIC_ID_TEE_OPENPERSISTENTOBJECT            0x00000903
#define TEE_PANIC_ID_TEE_RENAMEPERSISTENTOBJECT          0x00000904
#define TEE_PANIC_ID_TEE_CLOSEANDDELETEPERSISTENTOBJECT1 0x00000905
/* Persistent Object Enumeration */
#define TEE_PANIC_ID_TEE_ALLOCATEPERSISTENTOBJECTENUMERATOR 0x00000A01
#define TEE_PANIC_ID_TEE_FREEPERSISTENTOBJECTENUMERATOR     0x00000A02
#define TEE_PANIC_ID_TEE_GETNEXTPERSISTENTOBJECT            0x00000A03
#define TEE_PANIC_ID_TEE_RESETPERSISTENTOBJECTENUMERATOR    0x00000A04
#define TEE_PANIC_ID_TEE_STARTPERSISTENTOBJECTENUMERATOR    0x00000A05
/* Data Stream Access */
#define TEE_PANIC_ID_TEE_READOBJECTDATA             0x00000B01
#define TEE_PANIC_ID_TEE_SEEKOBJECTDATA             0x00000B02
#define TEE_PANIC_ID_TEE_TRUNCATEOBJECTDATA         0x00000B03
#define TEE_PANIC_ID_TEE_WRITEOBJECTDATA            0x00000B04
/* Generic Operation */
#define TEE_PANIC_ID_TEE_ALLOCATEOPERATION          0x00000C01
#define TEE_PANIC_ID_TEE_COPYOPERATION              0x00000C02
#define TEE_PANIC_ID_TEE_FREEOPERATION              0x00000C03
#define TEE_PANIC_ID_TEE_GETOPERATIONINFO           0x00000C04
#define TEE_PANIC_ID_TEE_RESETOPERATION             0x00000C05
#define TEE_PANIC_ID_TEE_SETOPERATIONKEY            0x00000C06
#define TEE_PANIC_ID_TEE_SETOPERATIONKEY2           0x00000C07
#define TEE_PANIC_ID_TEE_GETOPERATIONINFOMULTIPLE   0x00000C08
/* Message Digest */
#define TEE_PANIC_ID_TEE_DIGESTDOFINAL              0x00000D01
#define TEE_PANIC_ID_TEE_DIGESTUPDATE               0x00000D02
/* Symmetric Cipher */
#define TEE_PANIC_ID_TEE_CIPHERDOFINAL              0x00000E01
#define TEE_PANIC_ID_TEE_CIPHERINIT                 0x00000E02
#define TEE_PANIC_ID_TEE_CIPHERUPDATE               0x00000E03
/* MAC */
#define TEE_PANIC_ID_TEE_MACCOMPAREFINAL            0x00000F01
#define TEE_PANIC_ID_TEE_MACCOMPUTEFINAL            0x00000F02
#define TEE_PANIC_ID_TEE_MACINIT                    0x00000F03
#define TEE_PANIC_ID_TEE_MACUPDATE                  0x00000F04
/* Authenticated Encryption */
#define TEE_PANIC_ID_TEE_AEDECRYPTFINAL             0x00001001
#define TEE_PANIC_ID_TEE_AEENCRYPTFINAL             0x00001002
#define TEE_PANIC_ID_TEE_AEINIT                     0x00001003
#define TEE_PANIC_ID_TEE_AEUPDATE                   0x00001004
#define TEE_PANIC_ID_TEE_AEUPDATEAAD                0x00001005
/* Asymmetric */
#define TEE_PANIC_ID_TEE_ASYMMETRICDECRYPT          0x00001101
#define TEE_PANIC_ID_TEE_ASYMMETRICENCRYPT          0x00001102
#define TEE_PANIC_ID_TEE_ASYMMETRICSIGNDIGEST       0x00001103
#define TEE_PANIC_ID_TEE_ASYMMETRICVERIFYDIGEST     0x00001104
/* Key Derivation */
#define TEE_PANIC_ID_TEE_DERIVEKEY                  0x00001201
/* Random Data Generation */
#define TEE_PANIC_ID_TEE_GENERATERANDOM             0x00001301
/* Time */
#define TEE_PANIC_ID_TEE_GETREETIME                 0x00001401
#define TEE_PANIC_ID_TEE_GETSYSTEMTIME              0x00001402
#define TEE_PANIC_ID_TEE_GETTAPERSISTENTTIME        0x00001403
#define TEE_PANIC_ID_TEE_SETTAPERSISTENTTIME        0x00001404
#define TEE_PANIC_ID_TEE_WAIT                       0x00001405
/* Memory Allocation and Size of Objects */
#define TEE_PANIC_ID_TEE_BIGINTFMMCONTEXTSIZEINU32  0x00001501
#define TEE_PANIC_ID_TEE_BIGINTFMMSIZEINU32         0x00001502
/* Initialization */
#define TEE_PANIC_ID_TEE_BIGINTINIT                 0x00001601
#define TEE_PANIC_ID_TEE_BIGINTINITFMM              0x00001602
#define TEE_PANIC_ID_TEE_BIGINTINITFMMCONTEXT       0x00001603
/* Converter */
#define TEE_PANIC_ID_TEE_BIGINTCONVERTFROMOCTETSTRING 0x00001701
#define TEE_PANIC_ID_TEE_BIGINTCONVERTFROMS32         0x00001702
#define TEE_PANIC_ID_TEE_BIGINTCONVERTTOOCTETSTRING   0x00001703
#define TEE_PANIC_ID_TEE_BIGINTCONVERTTOS32           0x00001704
/* Logical Operation */
#define TEE_PANIC_ID_TEE_BIGINTCMP                  0x00001801
#define TEE_PANIC_ID_TEE_BIGINTCMPS32               0x00001802
#define TEE_PANIC_ID_TEE_BIGINTGETBIT               0x00001803
#define TEE_PANIC_ID_TEE_BIGINTGETBITCOUNT          0x00001804
#define TEE_PANIC_ID_TEE_BIGINTSHIFTRIGHT           0x00001805
/* Basic Arithmetic */
#define TEE_PANIC_ID_TEE_BIGINTADD                  0x00001901
#define TEE_PANIC_ID_TEE_BIGINTDIV                  0x00001902
#define TEE_PANIC_ID_TEE_BIGINTMUL                  0x00001903
#define TEE_PANIC_ID_TEE_BIGINTNEG                  0x00001904
#define TEE_PANIC_ID_TEE_BIGINTSQUARE               0x00001905
#define TEE_PANIC_ID_TEE_BIGINTSUB                  0x00001906
/* Modular Arithmetic */
#define TEE_PANIC_ID_TEE_BIGINTADDMOD               0x00001A01
#define TEE_PANIC_ID_TEE_BIGINTINVMOD               0x00001A02
#define TEE_PANIC_ID_TEE_BIGINTMOD                  0x00001A03
#define TEE_PANIC_ID_TEE_BIGINTMULMOD               0x00001A04
#define TEE_PANIC_ID_TEE_BIGINTSQUAREMOD            0x00001A05
#define TEE_PANIC_ID_TEE_BIGINTSUBMOD               0x00001A06
/* Other Arithmetic */
#define TEE_PANIC_ID_TEE_BIGINTCOMPUTEEXTENDEDGCD   0x00001B01
#define TEE_PANIC_ID_TEE_BIGINTISPROBABLEPRIME      0x00001B02
#define TEE_PANIC_ID_TEE_BIGINTRELATIVEPRIME        0x00001B03
/* Fast Modular Multiplication */
#define TEE_PANIC_ID_TEE_BIGINTCOMPUTEFMM           0x00001C01
#define TEE_PANIC_ID_TEE_BIGINTCONVERTFROMFMM       0x00001C02
#define TEE_PANIC_ID_TEE_BIGINTCONVERTTOFMM         0x00001C03

/*
 * The macro TEE_PARAM_TYPES can be used to construct a value that you can
 * compare against an incoming paramTypes to check the type of all the
 * parameters in one comparison, like in the following example:
 * if (paramTypes != TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
 *                                  TEE_PARAM_TYPE_MEMREF_OUPUT,
 *                                  TEE_PARAM_TYPE_NONE, TEE_PARAM_TYPE_NONE)) {
 *      return TEE_ERROR_BAD_PARAMETERS;
 *  }
 */
#define TEE_PARAM_TYPES(t0, t1, t2, t3) \
	((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

/*
 * The macro TEE_PARAM_TYPE_GET can be used to extract the type of a given
 * parameter from paramTypes if you need more fine-grained type checking.
 */
#define TEE_PARAM_TYPE_GET(t, i) ((((uint32_t)t) >> ((i)*4)) & 0xF)

/*
 * The macro TEE_PARAM_TYPE_SET can be used to load the type of a given
 * parameter from paramTypes without specifying all types (TEE_PARAM_TYPES)
 */
#define TEE_PARAM_TYPE_SET(t, i) (((uint32_t)(t) & 0xF) << ((i)*4))

/* Not specified in the standard */
#define TEE_NUM_PARAMS  4

/* TEE Arithmetical APIs */

#define TEE_BigIntSizeInU32(n) ((((n)+31)/32)+2)

#endif /* TEE_API_DEFINES_H */

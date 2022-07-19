#ifndef OSI__COMPILER_H__
#define OSI__COMPILER_H__

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif
#ifndef __LITTLE_ENDIAN_BITFIELD
#define __LITTLE_ENDIAN_BITFIELD
#endif
#define	__RTK_BYTE_ORDER	__LITTLE_ENDIAN

#define rtk_uswap_16(x) \
	((((x) & 0xff00) >> 8) | \
	 (((x) & 0x00ff) << 8))
#define rtk_uswap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))

#if __RTK_BYTE_ORDER == __LITTLE_ENDIAN
#define rtk_cpu_to_le16(x)		(x)
#define rtk_cpu_to_le32(x)		(x)
#define rtk_le16_to_cpu(x)		(x)
#define rtk_le32_to_cpu(x)		(x)
#define rtk_cpu_to_be16(x)		rtk_uswap_16(x)
#define rtk_cpu_to_be32(x)		rtk_uswap_32(x)
#define rtk_be16_to_cpu(x)		rtk_uswap_16(x)
#define rtk_be32_to_cpu(x)		rtk_uswap_32(x)
#else
#define rtk_cpu_to_le16(x)		rtk_uswap_16(x)
#define rtk_cpu_to_le32(x)		rtk_uswap_32(x)
#define rtk_le16_to_cpu(x)		rtk_uswap_16(x)
#define rtk_le32_to_cpu(x)		rtk_uswap_32(x)
#define rtk_cpu_to_be16(x)		(x)
#define rtk_cpu_to_be32(x)		(x)
#define rtk_be16_to_cpu(x)		(x)
#define rtk_be32_to_cpu(x)		(x)
#endif


#endif

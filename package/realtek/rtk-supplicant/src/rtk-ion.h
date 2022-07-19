#ifndef __RTK_ION_H__
#define __RTK_ION_H__

typedef int ion_user_handle_t;
typedef int HRESULT;
typedef void * HANDLE;
typedef off_t off64_t;

enum ion_heap_type {
 ION_HEAP_TYPE_SYSTEM,
 ION_HEAP_TYPE_SYSTEM_CONTIG,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ION_HEAP_TYPE_CARVEOUT,
 ION_HEAP_TYPE_CHUNK,
 ION_HEAP_TYPE_DMA,
 ION_HEAP_TYPE_CUSTOM,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ION_NUM_HEAPS = 16,
};

/* additional heaps used only on rtk_phoenix */
enum {
	RTK_PHOENIX_ION_HEAP_TYPE_TILER = ION_HEAP_TYPE_CUSTOM + 1,
	RTK_PHOENIX_ION_HEAP_TYPE_MEDIA,
	RTK_PHOENIX_ION_HEAP_TYPE_AUDIO,
	RTK_PHOENIX_ION_HEAP_TYPE_SECURE,
};

/**
 * @enum PIXEL_FORMAT
 */
typedef enum _PIXELFORMAT
{
    Format_8,           ///< 332
    Format_16,          ///< 565
    Format_32,          ///< 8888 ARGB
    Format_32_888A,			///< 8888 RGBA
    Format_2_IDX,
    Format_4_IDX,
    Format_8_IDX,
    Format_1555,
    Format_4444_ARGB,
    Format_4444_YUVA,
    Format_8888_YUVA,
    Format_5551,
    Format_4444_RGBA,
    Format_YUV420,
    Format_YUV422,
    Format_YUV444,
    NO_OF_PIXEL_FORMAT
} PIXEL_FORMAT;

#define RTK_PHOENIX_ION_HEAP_TILER_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_TILER)
#define RTK_PHOENIX_ION_HEAP_MEDIA_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_MEDIA)
#define RTK_PHOENIX_ION_HEAP_AUDIO_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_AUDIO)
#define RTK_PHOENIX_ION_HEAP_SECURE_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_SECURE)

#define ION_FLAG_NONCACHED              (1 << 31)
#define ION_FLAG_SCPUACC                (1 << 30)
#define ION_FLAG_ACPUACC                (1 << 29)

int ion_open();
int ion_alloc(int fd, size_t len, size_t align, unsigned int heap_mask,
              unsigned int flags, ion_user_handle_t *handle);
int ion_phys(int fd, ion_user_handle_t handle, unsigned long *addr, unsigned int *size);
int ion_map(int fd, ion_user_handle_t handle, size_t length, int prot,
            int flags, off64_t offset, unsigned char **ptr, int *map_fd);
int ion_free(int fd, ion_user_handle_t handle);
int ion_close(int fd);

#endif              /* __RTK_ION_H__ */
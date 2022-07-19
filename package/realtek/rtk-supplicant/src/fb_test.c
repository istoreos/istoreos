#include <linux/fb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#define swap16(x) ({						\
	u_int16_t __swap16gen_x = (x);					\
									\
	(u_int16_t)((__swap16gen_x & 0xff) << 8 |			\
	    (__swap16gen_x & 0xff00) >> 8);				\
})

#define pattern swap16((0x0 << 11 | 0x0 << 5 | 0x1f)) //RGB565	
//#define pattern swap16((0x01<<15 | 0x00 << 10 | 0x1f << 5 | 0x0)) //ARGB	
//#define pattern swap16((0x1f<<11 | 0x1f << 6 | 0x1f << 1 | 0x0))	//RGBA
#define ALPHA_VALUE 0x80
const char *FB_NAME = "/dev/fb0";
void*   m_FrameBuffer;
struct  fb_fix_screeninfo m_FixInfo;
struct  fb_var_screeninfo m_VarInfo;
int		m_FBFD;
enum dc_buffer_flags {
	eBuffer_AFBC_Enable            = 0x1U << 16,
	eBuffer_AFBC_Split             = 0x1U << 17,
	eBuffer_AFBC_YUV_Transform     = 0x1U << 18,
};
enum dc_buffer_id {
	eFrameBuffer            = 0x1U << 0,
	eFrameBufferSkip        = 0x1U << 4,
	eIONBuffer              = 0x1U << 1,
	eUserBurrer             = 0x1U << 2,
	eFrameBufferTarget      = 0x1U << 3,
};

enum dc_overlay_engine {
	eEngine_VO              = 0x1U << 0,
	eEngine_SE              = 0x1U << 1,
	eEngine_DMA             = 0x1U << 2,
	eEngine_MAX             = 0x1U << 3,
};

typedef enum
{
  INBAND_CMD_GRAPHIC_FORMAT_RGB565            = 4,    /* 16-bit RGB    (565)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB1555          = 5,    /* 16-bit ARGB   (1555) */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB8888          = 7,    /* 32-bit ARGB   (8888) */
  INBAND_CMD_GRAPHIC_FORMAT_RGBA5551          = 13,   /* 16-bit RGBA   (5551) */
  INBAND_CMD_GRAPHIC_FORMAT_RGBA8888          = 15,   /* 32-bit RGBA   (8888) */
  INBAND_CMD_GRAPHIC_FORMAT_RGB888            = 22,   /* 24-bit RGB    (888)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_RGB565_LITTLE     = 36,   /* litttle endian below */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB1555_LITTLE   = 37,
  INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE   = 39,
  INBAND_CMD_GRAPHIC_FORMAT_RGBA5551_LITTLE   = 45,
  INBAND_CMD_GRAPHIC_FORMAT_RGBA8888_LITTLE   = 47,
  INBAND_CMD_GRAPHIC_FORMAT_RGB888_LITTLE     = 54
} INBAND_CMD_GRAPHIC_FORMAT ;

#define DC2VO_IOC_MAGIC        'd'
#define DC2VO_IOC_MAXNR        32
#define DC2VO_WAIT_FOR_VSYNC             _IO    (DC2VO_IOC_MAGIC,  0)
#define DC2VO_SET_BUFFER_ADDR            _IO    (DC2VO_IOC_MAGIC,  1)
#define DC2VO_GET_BUFFER_ADDR            _IO    (DC2VO_IOC_MAGIC,  2)
#define DC2VO_SET_RING_INFO              _IO    (DC2VO_IOC_MAGIC,  3)
#define DC2VO_SET_OUT_RATE_INFO          _IO    (DC2VO_IOC_MAGIC,  4)
#define DC2VO_SET_DISABLE                _IO    (DC2VO_IOC_MAGIC,  5)
#define DC2VO_GET_SURFACE                _IO    (DC2VO_IOC_MAGIC,  6)
#define DC2VO_SET_MODIFY                 _IO    (DC2VO_IOC_MAGIC,  7)
#define DC2VO_GET_MAX_FRAME_BUFFER       _IO    (DC2VO_IOC_MAGIC,  8)
#define DC2VO_GET_SYSTEM_TIME_INFO       _IO    (DC2VO_IOC_MAGIC,  9)
#define DC2VO_SET_SYSTEM_TIME_INFO       _IO    (DC2VO_IOC_MAGIC, 10)
#define DC2VO_GET_CLOCK_MAP_INFO         _IO    (DC2VO_IOC_MAGIC, 11)
#define DC2VO_GET_CLOCK_INFO             _IO    (DC2VO_IOC_MAGIC, 12)
#define DC2VO_RESET_CLOCK_TABLE          _IO    (DC2VO_IOC_MAGIC, 13)
#define DC2VO_SET_ION_SHARE_MEMORY       _IO    (DC2VO_IOC_MAGIC, 17)
#define DC2VO_SET_BUFFER_INFO            _IO    (DC2VO_IOC_MAGIC, 18)
#define DC2VO_SET_BG_SWAP                _IO    (DC2VO_IOC_MAGIC, 19)
#define DC2VO_SET_GLOBAL_ALPHA           _IO    (DC2VO_IOC_MAGIC, 20)
#define DC2VO_SET_VSYNC_FORCE_LOCK       _IO    (DC2VO_IOC_MAGIC, 21)
#define DC2VO_SIMPLE_POST_CONFIG         _IO    (DC2VO_IOC_MAGIC, 22)
#define USE_GLOBAL_ALPHA	1<<19
struct dc_buffer_rect {
	unsigned int left;
	unsigned int top;
	unsigned int right;
	unsigned int bottom;
};

struct dc_buffer {
	unsigned int            id;                 /* enum dc_buffer_id */
	unsigned int            overlay_engine;     /* enum dc_overlay_engine */
	struct dc_buffer_rect   sourceCrop;
	struct dc_buffer_rect   displayFrame;       /* base on framebuffer */
	unsigned int            format;
	unsigned int            offset;
	unsigned int            phyAddr;
	unsigned int            width;
	unsigned int            height;
	unsigned int            stride;
	unsigned int            context;
	int64_t                 pts;
	unsigned int            flags;
    unsigned int            plane_alpha; 
    unsigned int            colorkey; 
	unsigned int            reserve[30];
	int64_t                 acquire_fence_fd;   /* user   space : fenceFd (input) */
};
struct dc_simple_post_config {
	struct dc_buffer        buf;
	int                     complete_fence_fd;
};
int main() {

	struct dc_simple_post_config config;
	int iFrameBufferSize;
	uint32_t vPlanePhy;
	uint64_t vPlaneVirt;
	/* Open the framebuffer device in read write */
	m_FBFD = open(FB_NAME, O_RDWR);
	if (m_FBFD < 0) {
		printf("Unable to open %s.\n", FB_NAME);
		return 1;
	}
	/* Do Ioctl. Retrieve fixed screen info. */
	if (ioctl(m_FBFD, FBIOGET_FSCREENINFO, &m_FixInfo) < 0) {
		printf("get fixed screen info failed: %s\n",
				strerror(errno));
		close(m_FBFD);
		return 1;
	}
	/* Do Ioctl. Get the variable screen info. */
	if (ioctl(m_FBFD, FBIOGET_VSCREENINFO, &m_VarInfo) < 0) {
		printf("Unable to retrieve variable screen info: %s\n",
				strerror(errno));
		close(m_FBFD);
		return 1;
	}
	vPlanePhy=m_FixInfo.smem_start; //get PA from FB driver

	memset(&config, 0, sizeof(config));
	config.buf.sourceCrop.left=0;
	config.buf.sourceCrop.right=1920;
	config.buf.sourceCrop.top=0;
	config.buf.sourceCrop.bottom=1080;
	config.buf.displayFrame.left=0;
	config.buf.displayFrame.right=1920;
	config.buf.displayFrame.top=0;
	config.buf.displayFrame.bottom=1080;

	config.buf.width=m_VarInfo.xres;
	config.buf.height=m_VarInfo.yres;
	config.buf.stride=m_FixInfo.line_length;
	config.buf.id = eFrameBufferTarget;
	config.buf.overlay_engine = eEngine_VO;
	config.buf.acquire_fence_fd = -1;
	config.buf.phyAddr =  vPlanePhy; //set display buffer
	config.buf.colorkey = 0xff000000;   //format:ARGB, set -1 to disable color key
	config.buf.format = INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE;
	if (config.buf.format == INBAND_CMD_GRAPHIC_FORMAT_RGB565)
		config.buf.plane_alpha=ALPHA_VALUE; //plane alpha is available if pixel alpha is off

	/* Calculate the size to mmap */
	iFrameBufferSize = m_FixInfo.line_length * m_VarInfo.yres;
	printf("Line length %d %d %d %d\n", m_FixInfo.line_length, m_VarInfo.yres, m_VarInfo.xres,iFrameBufferSize);
	/* Now mmap the framebuffer. */
	m_FrameBuffer = mmap(NULL, iFrameBufferSize*2, PROT_READ | PROT_WRITE,
			MAP_SHARED, m_FBFD,0);
	if (m_FrameBuffer == NULL) {
		printf("mmap failed:\n");
		close(m_FBFD);
		return 1;
	}
	vPlaneVirt=(uint64_t)m_FrameBuffer;
	printf("smem_start %x, smem_len %d, video plane %x  %x\n",m_FixInfo.smem_start, m_FixInfo.smem_len, vPlanePhy,vPlaneVirt);
	ioctl(m_FBFD, DC2VO_SIMPLE_POST_CONFIG, &config);
	{
		uint32_t *p = (void *) m_FrameBuffer;
		uint16_t x,y=0;
//printf("%s %s %d  %d %d %p 0x%x\n",__FILE__,__func__,__LINE__, m_VarInfo.yres, m_VarInfo.xres, m_FrameBuffer, pattern);
			for (y=0; y<m_VarInfo.yres; y++) {
				for (x=0; x<m_VarInfo.xres; x++) {
					if (y<(m_VarInfo.yres/2))
					p[x + y * m_VarInfo.xres] = 0xff000000;
					else
					p[x + y * m_VarInfo.xres] = 0xffffffff;
				}
			}
	}
}

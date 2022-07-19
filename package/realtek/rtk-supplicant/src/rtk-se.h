#ifndef __RTK_SE_H__
#define __RTK_SE_H__

HRESULT
se_open(void);
HRESULT
se_close(void);

HRESULT
SE_Memcpy_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int size,
            HANDLE hQueue);

HRESULT
SE_2DMemcpy_API( unsigned int dstPAddr, unsigned int srcPAddr,
        int nDstStride,
        int nDstSliceHeight,
        int nSrcStride,
        int nSrcSliceHeight,
        int nWidth,
        int nHeight,
        HANDLE hQueue);

HRESULT
SE_2DMemcpyNVR_API( unsigned int dstPAddr, unsigned int srcPAddr,
        int nDstStride,
        int nSrcStride,
        int nWidth,
        int nHeight,
        PIXEL_FORMAT fmt,
        HANDLE hQueue);

HRESULT
SE_Scaler_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidht,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue,
            unsigned int interlace);

HRESULT
SE_Yuv420ToArgb_API(unsigned int dstPAddr, unsigned int srcPAddr,
        int nWidth, int nHeight,
        HANDLE hQueue);

#endif				/* __RTK_SE_H__ */
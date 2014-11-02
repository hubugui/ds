#ifndef __HISTOGRAM__
#define __HISTOGRAM__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * support all planar YUV format
 */
void histogram_planar_yuv(unsigned char *yuv, size_t width, size_t height, size_t *htg);

/**
 * http://zh.wikipedia.org/wiki/%E5%A4%A7%E6%B4%A5%E7%AE%97%E6%B3%95
 */
unsigned char histogram_otsu_threshold(size_t width, size_t height, size_t *htg);

#ifdef __cplusplus
}
#endif
#endif
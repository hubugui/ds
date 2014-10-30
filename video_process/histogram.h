#ifndef __HISTOGRAM__
#define __HISTOGRAM__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * planar YUV
 */
void histogram_planar(const unsigned char *yuv, size_t width, size_t height, size_t *values);

#ifdef __cplusplus
}
#endif
#endif

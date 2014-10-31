#ifndef __YUV_FILE__
#define __YUV_FILE__

#ifdef __cplusplus
extern "C" {
#endif

unsigned char *yuv_i420_read(const char *filepath, size_t width, size_t height);
unsigned char *yuv_i420_write(const char *filepath, size_t width, size_t height, unsigned char *yuv);

#ifdef __cplusplus
#endif
#endif

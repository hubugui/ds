#ifndef __BINARY_IMAGE__
#define __BINARY_IMAGE__

#ifdef __cplusplus
extern "C" {
#endif

void binary_image_i420(unsigned char *yuv, size_t width, size_t height, unsigned char threshold);

void binary_image_adapter_threshold_mean(unsigned char *src,
                                        unsigned char *dst,
                                        size_t width, 
                                        size_t height, 
                                        size_t block_size, 
                                        int adjust);

#ifdef __cplusplus
}
#endif
#endif
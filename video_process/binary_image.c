#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_image.h"

void binary_image_i420(unsigned char *yuv, size_t width, size_t height, unsigned char threshold) {
    size_t i, j;
    unsigned char *buffer;

    /* Y */
    for (i = 0; i < height; i++) {
        buffer = yuv + i * width;
        for (j = 0; j < width; j++) {
            buffer[j] = buffer[j] <= threshold ? 0 : 0xff;
        }
    }

    /* UV */
    /* memset(yuv + width * height, 0xff, width * (height >> 1)); */
}

void binary_image_adapter_threshold_mean(unsigned char *src,
                                        unsigned char *dst,
                                        size_t width, 
                                        size_t height, 
                                        size_t block_size, 
                                        int adjust) {
    size_t i, j, m, n;
    unsigned char *src_row, *dst_row, *point, mean;
    int sum;

    /* Y */
    for (i = 0; i < height; i++) {
        src_row = src + i * width;
        dst_row = dst + i * width;
        for (j = 0; j < width; j++) {
            if (i + block_size < height && j + block_size < width) {
                for (sum = m = 0; m < block_size; m++) {
                    point = src_row + m * width;
                    for (n = 0; n < block_size; n++) {
                        sum += point[j+n];
                    }
                }
                mean = (unsigned char) (sum / (block_size * block_size) - adjust);
                dst_row[j] = src_row[j] <= mean ? 0 : 0xff;
            } else {
                dst_row[j] = 0xff;
            }
        }
    }

    /* UV */
    memset(dst + width * height, 0x7f, width * (height >> 1));
}
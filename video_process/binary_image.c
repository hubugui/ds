#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_image.h"

void binary_image_i420(unsigned char *yuv, size_t width, size_t height, unsigned char threshold) {
    size_t i, j;
    char *buffer;

    /* Y */
    for (i = 0; i < height; i++) {
        buffer = yuv + i * width;
        for (j = 0; j < width; j++) {
            buffer[j] = buffer[j] < threshold ? 0 : 255;
        }
    }
    
    /* UV */
    memset(yuv + width * height, 0x00, width * (height > 1));
}

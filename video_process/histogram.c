#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void histogram_planar(const unsigned char *yuv, size_t width, size_t height, size_t *values) {
    size_t i, j;
    char *buffer;

    memset(values, 0, 255);
    for (i = 0; i < height; i++) {
        buffer = yuv + i * width;
        for (j = 0; j < width; j++) {
            values[buffer[j]]++;
        }
    }
}

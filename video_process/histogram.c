#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void histogram_planar(const unsigned char *yuv, size_t width, size_t height, size_t *values) {
    size_t i, j;
    unsigned char *buffer;

    memset(values, 0, 0xff);
    for (i = 0; i < height; i++) {
        buffer = (unsigned char *) yuv + i * width;
        for (j = 0; j < width; j++) {
            values[buffer[j]]++;
        }
    }
}

unsigned char histogram_overall_threshold(size_t *values) {
    unsigned char threshold = 0x00;
    //unsigned char peak[0xff] = 0x00;
    unsigned char i, min, max;

    for (i = 0, min = max = values[0]; i < 0xff; i++) {
        if (values[i] < min)
            min = values[i];
        if (values[i] > max)
            max = values[i];
    }      

    return threshold;
}

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void histogram_planar(unsigned char *yuv, size_t width, size_t height, size_t *values) {
    size_t i;

    memset(values, 0x00, (0xff+1) * sizeof(size_t));
    for (i = 0; i < width * height; i++) {
        values[yuv[i]]++;
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

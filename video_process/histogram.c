#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

void histogram_planar_yuv(unsigned char *yuv, size_t width, size_t height, size_t *htg) {
    size_t i;

    memset(htg, 0x00, (0xff+1) * sizeof(size_t));
    for (i = 0; i < width * height; i++) {
        htg[yuv[i]]++;
    }
}

unsigned char histogram_otsu_threshold(size_t width, size_t height, size_t *htg) {
    unsigned char threshold = 0x00;
    size_t i, numbers[256], grays[256];
    double w0, w1, u0, u1, g, max_g;
    double pixels = width * height;

    /* foreground/background total pixels and grays of per gray level */
    for (i = 0; i <= 0xff; i++) {
        if (i > 0) {
            numbers[i] = numbers[i-1] + htg[i];
            grays[i] = grays[i-1] + i * htg[i];
        } else {
            numbers[i] = htg[i];
            grays[i] = 0;
        }
    }

    /* OTSU */
    for (i = 0, max_g = 0.0f; i <= 0xff; i++) {
        /* number of per gray level */
        w0 = numbers[i] / pixels;
        w1 = 1.0f - w0;
        /* avg gray of per gray level, avoid zero */
        u0 = numbers[i] > 0 ? grays[i] / numbers[i] : 0.0f;
        u1 = numbers[0xff] == numbers[i] ? 
            0.0f : (grays[0xff] - grays[i]) / (numbers[0xff] - numbers[i]);

        g = w0 * w1 * (u0 - u1) * (u0 - u1);
        if (g > max_g) {
            max_g = g;
            threshold = i;
        }
    }
    return threshold;
}
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_image.h"
#include "histogram.h"
#include "file_rw.h"

#define YUV_I420_SIZE(w,h)  ((w >> 1) * height * 3)

int main(int argc, char **argv) {
    char in[256] = "test_612_816.yuv";
    char out[256] = "test_612_816_bw.yuv";
    size_t width = 612, height = 816;
    size_t  htg[256];
    unsigned char *in_yuv, threshold;

    if (argc > 3) {
        char *prefix = strstr(argv[1], ".yuv");
        size_t len = prefix - argv[1];

        memmove(in, argv[1], len);
        in[len] = 0x00;
        sprintf(out, "%s_bw.yuv", in);

        strcpy(in, argv[1]);
        width = atoi(argv[2]);
        height = atoi(argv[3]);
    }

    /* read i420 */
    in_yuv = file_read(in, YUV_I420_SIZE(width, height)); 
    if (!in_yuv) {
        printf("cannot read yuv, file path is '%s'\n", in);
        return -1;
    }

    /* calc histogram */
    histogram_planar_yuv(in_yuv, width, height, htg);

    /* OTSU threshold */
    threshold = histogram_otsu_threshold(width, height, htg);
    printf("histogram_otsu_threshold()=%d\n", threshold);
    binary_image_i420(in_yuv, width, height, threshold);

    /* black white image */
    file_write(out, YUV_I420_SIZE(width, height), in_yuv);
    free(in_yuv);
    return 0;
}
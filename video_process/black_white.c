#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_image.h"
#include "histogram.h"
#include "file_rw.h"

#define YUV_I420_SIZE(w,h)  ((w >> 1) * height * 3)

int main(int argc, char **argv) {
    char in[256] = "test_612_816.yuv";
    char out[256] = "test_612_816_bw_OTSU.yuv";
    char out_mean[256] = "test_612_816_bw_MEAN.yuv";
    size_t width = 612, height = 816;
    size_t block_size = 3;
    int adjust = 15;
    size_t  htg[256];
    unsigned char *in_yuv, *out_yuv, threshold;

    if (argc > 3) {
        char *prefix = strstr(argv[1], ".yuv");
        size_t len = prefix - argv[1];

        memmove(in, argv[1], len);
        in[len] = 0x00;
        sprintf(out, "%s_bw_OTSU.yuv", in);
        sprintf(out_mean, "%s_bw_MEAN.yuv", in);        

        strcpy(in, argv[1]);
        width = atoi(argv[2]);
        height = atoi(argv[3]);

        if (argc >= 5) {
            block_size = atoi(argv[4]);
            adjust = atoi(argv[5]);
        }
    }

    /* read i420 */
    in_yuv = file_read(in, YUV_I420_SIZE(width, height)); 
    if (!in_yuv) {
        printf("cannot read yuv, file path is '%s'\n", in);
        return -1;
    }

    /* local MEAN */
    out_yuv = malloc(YUV_I420_SIZE(width, height));
    if (!out_yuv) {
        free(in_yuv);
        printf("cannot malloc(%d)\n", YUV_I420_SIZE(width, height));
        return -1;
    }  
    binary_image_adapter_threshold_mean(in_yuv, out_yuv, width, height, block_size, adjust);
    file_write(out_mean, YUV_I420_SIZE(width, height), out_yuv);

    /* overall OTSU */
    histogram_planar_yuv(in_yuv, width, height, htg);
    threshold = histogram_otsu_threshold(width, height, htg);
    printf("histogram_otsu_threshold()=%d\n", threshold);
    binary_image_i420(in_yuv, width, height, threshold);
    file_write(out, YUV_I420_SIZE(width, height), in_yuv);    

    free(out_yuv);
    free(in_yuv);
    return 0;
}
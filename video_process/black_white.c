#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_histogram.h>

#include "binary_image.h"
#include "histogram.h"
#include "file_rw.h"

#define YUV_I420_SIZE(w,h)  ((w >> 1) * height * 3)

int main(int argc, char **argv) {
    char *in = "test_612_816.yuv";
    char out[255];
    size_t width, height, htg[255];
    unsigned char *in_yuv, threshold;

    if (argc > 2)
        in = argv[1];
    sscanf(in, "test_%zu_%zu.yuv", &width, &height);
    sprintf(out, "test_%zu_%zu_bw.yuv", width, height);

    /* read i420 */
    in_yuv = file_read(in, YUV_I420_SIZE(width, height)); 
    if (!in_yuv) {
        printf("cannot read yuv, file path is '%s'\n", in);
        return -1;
    }

    /* calc histogram */
    histogram_planar((const unsigned char *) in_yuv, width, height, htg);

    {
        unsigned char i;

        gsl_histogram *h = gsl_histogram_alloc (0xff);
        gsl_histogram_set_ranges_uniform (h, 0xff, 0xff);

        for (i = 0; i < 0xff; i++) {
            gsl_histogram_increment(h, htg[i] + 0.0);
        }
        gsl_histogram_fprintf(stdout, h, "%g", "%g");
        gsl_histogram_free(h);
    }

    /* overall threshold */
    threshold = histogram_overall_threshold(htg);
    binary_image_i420(in_yuv, width, height, threshold);

    /* black white image */
    file_write(out, YUV_I420_SIZE(width, height), in_yuv);
    free(in_yuv);
    return 0;
}

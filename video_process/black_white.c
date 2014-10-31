#include <memory.h>
#include <stdio.h>

#include "binary_image.h"
#include "histogram.h"
#include "yuv_file.h"

int main(int argc, char **argv) {
    char *in = "test_612_816.yuv";
    char out[255];
    size_t width, height;
    size_t htg[255];
    unsigned char *in_yuv;

    if (argc > 2)
        in = argv[1];
    sscanf("test_%zu_%zu.yuv", in, &width, &height);
    sprintf("test_%zu_%zu_bw.yuv", out, width, height);

    /* read i420 */
    in_yuv = yuv_i420_read(in, 612, 816); 
    if (!in_yuv) {
        printf("cannot read yuv, file path is '%s'\n", in);
        return -1;
    }

    /* calc histogram */
    histogram_planar((const unsigned char *) in_yuv, width, height, htg);

    /* middle value */
    binary_image_i420(in_yuv, width, height, 0x77);

    yuv_i420_write(out, width, height, in_yuv);
    free((char *) in_yuv);
    return 0;
}

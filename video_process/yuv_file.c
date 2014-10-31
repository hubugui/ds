#include <memory.h>
#include <stdio.h>

unsigned char *yuv_i420_read(const char *filepath, size_t width, size_t height) {
    size_t size = (width >> 1) * height * 3;
    unsigned char *yuv = NULL;
    FILE *fd;

    if (fd = fopen(filepath, "rb")) {
        yuv = malloc(size);
        if (yuv) {
            if (fread(yuv, 1, size, fd) != size) {
                free(yuv);
                yuv = NULL;
            }
        }
        fclose(fd);
    } 
    return yuv;
}

unsigned char *yuv_i420_write(const char *filepath, size_t width, size_t height, unsigned char *yuv) {
    size_t size = (width >> 1) * height * 3;
    FILE *fd;

    if (fd = fopen(filepath, "wb")) {
        if (fwrite(yuv, 1, size, fd) != size)
            yuv = NULL;
        fclose(fd);
    } else
        yuv = NULL;
    return yuv;
}

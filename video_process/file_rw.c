#include <stdio.h>
#include <stdlib.h>

#include "file_rw.h"

unsigned char *file_read(const char *filepath, size_t size) {
    unsigned char *buffer = NULL;
    FILE *fd;

    if ((fd = fopen(filepath, "rb"))) {
        buffer = malloc(size);
        if (buffer) {
            if (fread(buffer, 1, size, fd) != size) {
                free(buffer);
                buffer = NULL;
            }
        }
        fclose(fd);
    } 
    return buffer;
}

size_t file_write(const char *filepath, size_t size, unsigned char *buffer) {
    FILE *fd;

    if ((fd = fopen(filepath, "wb"))) {
        if (fwrite(buffer, 1, size, fd) != size)
            size = 0;
        fclose(fd);
    } else
        size = 0;
    return size;
}

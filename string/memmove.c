#include "memmove.h"

void 
_memmove(char *dst, const char *src, unsigned int size) {
    if (dst <= src || src + size < dst) {
        while (size) {
            *dst++ = *src++;
            size--;
        }
    } else {
        while (size) {
            dst[size-1] = src[size-1];
            size--;
        }
    }
}

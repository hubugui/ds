#include <stdlib.h>
#include "memmove.h"

void * 
_memmove(void *dst, const void *src, size_t size) {
    void *result = dst;
    size_t *dst_w = (size_t *) dst;
    size_t *src_w = (size_t *) src;
    size_t quot = size / sizeof(size_t); 
    size_t remi = size % sizeof(size_t);

    dst += quot * sizeof(size_t);
    src += quot * sizeof(size_t);
    if (dst_w <= src_w) {
        while (quot--) {
            *dst_w++ = *src_w++;
        }
        while (remi--) {
            *(char *) dst++ = *(char *) src++;
        }
    } else {
        dst += remi;
        src += remi;
        while (remi--) {
            *(char *) --dst = *(char *) --src;
        }
        dst_w += quot; 
        src_w += quot; 
        while (quot--) {
            *--dst_w = *--src_w;
        }
    }
    return result;
}

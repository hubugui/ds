#include <stdlib.h>
#include "memmove.h"

#if __WORDSIZE == 32
#define word_int  int 
#elif __WORDSIZE == 64
#define word_int  long long int
#else
#error "unknown platform"
#endif

void * 
_memmove(void *dst, const void *src, size_t size) {
    void *result = dst;
    word_int *dst_w = (word_int *) dst;
    word_int *src_w = (word_int *) src;
    size_t quot = size / sizeof(void *); 
    size_t remi = size % sizeof(void *);

    dst += quot * sizeof(void *);
    src += quot * sizeof(void *);
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

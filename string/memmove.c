#include "memmove.h"

#define PLATFORM_BITS   (sizeof(void *) * 8)

#if PLATFORM_BITS == 32
#define word_size  int 
#elif PLATFORM_BITS == 64
#define word_size  long long int
#else
#error "unknown platform"
#endif

void * 
_memmove(void *dst, const void *src, unsigned int size) {
    void *result = dst;
    word_size *dst_i = (word_size) dst;
    word_size *src_i = (word_size) src;
    size_t quot = size / sizeof(void *); 
    size_t remi = size % sizeof(void *);

    dst += quot * sizeof(void *);
    src += quot * sizeof(void *);
    if (dst_i <= src_i) {
        while (quot) {
            *dst_i++ = *src_i++;
            quot--;
        }
        while (remi) {
            *dst++ = *src++;
            remi--;
        }
    } else {
        while (quot) {
            dst[size-1] = src[size-1];
            quot--;
        }
    }

    return result;
}

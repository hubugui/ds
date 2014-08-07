#ifndef __KUAN_ARRAY__
#define __KUAN_ARRAY__

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * for example array size is 2, 
 * kuan_array_next() will be return sequence as follow:
 *
 * 0 0
 * 0 1
 * 1 0
 * 1 1
 *
 * total (n ^ n) combination 
 */

struct kuan_array;

struct kuan_array *kuan_array_new(size_t size);
void kuan_array_delete(struct kuan_array *ka);

int kuan_array_next(struct kuan_array *ka, size_t *value);

#ifdef __cplusplus
}
#endif
#endif
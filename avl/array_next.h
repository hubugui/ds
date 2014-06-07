#ifndef __ARRAY_NEXT__
#define __ARRAY_NEXT__

#ifdef __cplusplus
extern "C" {
#endif

struct array_next;

struct array_next *array_next_new(size_t size);
void array_next_delete(struct array_next *an);

int array_next_next(struct array_next *an, size_t *value);

#ifdef __cplusplus
}
#endif
#endif

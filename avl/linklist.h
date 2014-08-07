#ifndef __LINKLIST__
#define __LINKLIST__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * non-thread safe
 */

struct linklist;
struct linklist_node;

struct linklist *linklist_new(void);
void linklist_delete(struct linklist *list);
size_t linklist_size(struct linklist *list);

int linklist_insert(struct linklist *list, void *value, void *userdata1, void *userdata2);
void *linklist_remove_head(struct linklist *list, void **userdata1_p, void **userdata2_p);

#ifdef __cplusplus
}
#endif
#endif

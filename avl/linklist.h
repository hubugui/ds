#ifndef __LINKLIST__
#define __LINKLIST__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * not thread safe
 */

struct linklist;
struct linklist_node;

struct linklist *linklist_new(void);
void linklist_delete(struct linklist *list);

int linklist_insert(struct linklist *list, void *value, void *userdata);
void *linklist_remove_head(struct linklist *list, void **userdata_p);

#ifdef __cplusplus
}
#endif
#endif

#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

static int _pre_depth = 1;

static void 
_dump(void *value) {
    printf("%ld ", (size_t) value);
}

static void 
_bfs_dump(void *value, int depth) {
    if (_pre_depth != depth)
        printf("\n");
    printf("%ld(%d) ", (size_t) value, depth);
    _pre_depth = depth;
}

static int 
_compare(void *v1, void *v2) {
    if (v1 > v2)
        return 1;
    if (v1 < v2)
        return -1;
    return 0;
}

int
main(int argc, char **argv) {
    int i;
    struct avl *t = avl_new();

    if (!t) {
        printf("avl_new() fail\n");
        return -1;
    }
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (avl_insert(t, (void *) (atoll(argv[i])), _compare)) {
                printf("avl_insert() fail\n");
                goto fail;
            }
        }
    } else {
        
    }

    avl_bfs(t, _bfs_dump);
    _pre_depth = 1;
    printf("\n");
    
    if (avl_verify(t) == 0)
        printf("verify success.\n");
    else
        printf("verify fail.\n");

fail:
    avl_delete(t);
    return 0;
}

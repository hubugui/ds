#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

static long long int _pre_idx_inline = -1;
static long long int _pre_depth = -1;
static int _height;

static int 
_compare(void *v1, void *v2) {
    if (v1 > v2)
        return 1;
    if (v1 < v2)
        return -1;
    return 0;
}

static void 
_bfs_dump(void *value, long long int depth, long long int idx) {
    long long int upper_nb = (long long int) pow(2, depth) - 1;
    long long int i, j, idx_inline = idx - upper_nb;
    long long int pow_unit = (long long int) pow(2, _height - depth);
    char *unit = "  ";

    long long int left_unit = pow_unit - 1;
    long long int node_unit = 2 * pow_unit - 1;

    if (depth == _pre_depth) {
        for (i = 0; i < (idx_inline - _pre_idx_inline) * (1 + node_unit) - 1; i++) {
            printf("%s", unit);
        }
    } else {
        for (i = 0; i < left_unit; i++) {
            printf("%s", unit);
        }
        for (i = 0; i < idx_inline * (1+node_unit); i++) {
            printf("%s", unit);
        }
    }
    printf("%02lld", (long long int) value);
    if (idx + 2 == (long long int) pow(2, depth+1))
        printf("\n");
     _pre_idx_inline = idx_inline;
     _pre_depth = depth;
}

int
main(int argc, char **argv) {
    int i, rc;
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

    _height = avl_height(t);
    avl_bfs(t, _bfs_dump);
    _pre_depth = -1;
    printf("\n");

    rc = avl_verify(t);            
    if (rc == -1)
        printf("verify fail in height.\n");
    else if (rc == -2)
        printf("verify fail in parent point.\n");

fail:
    avl_delete(t);
    return 0;
}

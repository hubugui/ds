#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "array_next.h"

static long long int _pre_idx_line = -1;
static long long int _pre_depth = -1;
static int _height;

static int 
_compare(void *v1, void *v2)
{
    if ((size_t) v1 > (size_t) v2)
        return 1;
    if ((size_t) v1 < (size_t) v2)
        return -1;
    return 0;
}

static void 
_bfs_dump(void *value, long long int depth, long long int idx)
{
    long long int i, idx_line = idx - (((long long int) pow(2, depth)) - 1);
    long long int pow_unit = (long long int) pow(2, _height - depth);
    char *unit = "  ";

    long long int left_unit = pow_unit - 1;
    long long int node_unit = 2 * pow_unit - 1;

    if (depth == _pre_depth) {
        for (i = 0; i < (idx_line - _pre_idx_line) * (1 + node_unit) - 1; i++) {
            printf("%s", unit);
        }
    } else {
        if (depth > 0)
            printf("\n");
        for (i = 0; i < left_unit; i++) {
            printf("%s", unit);
        }
        for (i = 0; i < idx_line * (1+node_unit); i++) {
            printf("%s", unit);
        }
    }
    printf("%02lld", (long long int) value);
     _pre_idx_line = idx_line;
     _pre_depth = depth;
}

static void _bfs(struct avl *t)
{
    int rc;

    _height = avl_height(t);
    avl_bfs(t, _bfs_dump);
    _pre_depth = -1;
    printf("\n");

    rc = avl_verify(t);
    if (rc == -1) {
        printf("verify fail in height.\n");
        exit(rc);
    } else if (rc == -2) {
        printf("verify fail in parent point.\n");
        exit(rc);
    }
}

static int 
_arg(int argc, char **argv)
{
    int rc = 0, i;
    struct avl *t = avl_new();

    if (!t) {
        printf("avl_new() fail\n");
        return -1;
    }
    /* insert */
    for (i = 1; i < argc - 1; i++) {
        if (avl_insert(t, (void *) (long int) (atoll(argv[i])), _compare)) {
            printf("avl_insert(%d) fail\n", (int) (atoll(argv[argc - 1])));
            rc = -1;
            goto fail;
        }        
    }
    _bfs(t);

    /* remove last element */
    if (avl_remove(t, (void *) (long int) (atoll(argv[argc - 1])), _compare)) {
        printf("avl_remove(%d) fail\n", (int) (atoll(argv[argc - 1])));
        rc = -1;
        goto fail;
    }
    _bfs(t);
fail:
    avl_delete(t);
    return rc;
}

static int 
_array(int size)
{
    int rc = -1, i;
    size_t value[1024];
    struct array_next *an = array_next_new(size);
    struct avl *t = NULL;

    while ((rc = array_next_next(an, value) == 0)) {
        t = avl_new();
        if (!t) {
            printf("avl_new() fail\n");
            goto fail;
        }

        for (i = 0; i < size; i++) {
            printf("%ld ", value[i]);
            if (avl_insert(t, (void *) (value[i]), _compare)) {
                printf("avl_insert() fail\n");
                goto fail;
            }
        }
        printf("\n");
        rc = avl_verify(t); 
        if (rc == -1) {
            printf("verify fail in height.\n");
            exit(rc);
        } else if (rc == -2) {
            printf("verify fail in parent point.\n");
            exit(rc);
        }
        avl_delete(t);
        t = NULL;
    }

    rc = 0;
fail:
    array_next_delete(an);
    if (t)
        avl_delete(t);
    return rc;
}

int 
main(int argc, char **argv)
{
    if (argc > 2)
        return _arg(argc, argv);
     else
        return _array(atoi(argv[1]));
}

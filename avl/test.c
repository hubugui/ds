#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "kuan_array.h"

static int _compare(void *v1, void *v2)
{
    if ((size_t) v1 > (size_t) v2)
        return 1;
    if ((size_t) v1 < (size_t) v2)
        return -1;
    return 0;
}

static void _verify(struct avl *avl)
{
    int rc = avl_verify(avl, _compare);

    if (rc == -1) {
        printf("fail! in verify node's height.\n");
        exit(rc);
    } else if (rc == -2) {
        printf("fail! in node's parent point.\n");
        exit(rc);
    } else if (rc == -3) {
        printf("fail! in node's value.\n");
        exit(rc);
    }
}

static void _dump(void *value)
{
    printf("%02lld", (long long int) value);
}

static int _arg(int argc, char **argv)
{
    int rc = 0, i;
    struct avl *avl = avl_new();

    if (!avl) {
        printf("avl_new() fail\n");
        return -1;
    }
    /* insert */
    for (i = 1; i < argc - 1; i++) {
        if (avl_insert(avl, (void *) (long int) (atoll(argv[i])), _compare)) {
            printf("avl_insert(%d) fail\n", (int) (atoll(argv[argc - 1])));
            rc = -1;
            goto fail;
        }        
    }
    avl_bfs_dump(avl, _dump);
    _verify(avl);

    /* remove last element */
    if (avl_remove(avl, (void *) (long int) (atoll(argv[argc - 1])), _compare)) {
        printf("avl_remove(%d) fail\n", (int) (atoll(argv[argc - 1])));
        rc = -1;
        goto fail;
    }
    avl_bfs_dump(avl, _dump);
    _verify(avl);

    printf("success!\n");
fail:
    avl_delete(avl);
    return rc;
}

static int _array(int size)
{
    int rc = -1, i, count = 0;
    size_t value[1024] = {0};
    struct kuan_array *ka = kuan_array_new(size);
    struct avl *avl = NULL;

    while ((rc = kuan_array_next(ka, value) == 0)) {
        avl = avl_new();
        if (!avl) {
            printf("avl_new() fail\n");
            goto fail;
        }

        //printf("%d>", ++count);

        for (i = 0; i < size; i++) {
            //printf("%ld ", value[i]);
            if (avl_insert(avl, (void *) (value[i]), _compare)) {
                printf("avl_insert() fail\n");
                goto fail;
            }
        }
        //printf("pass\n");
        _verify(avl);
        avl_delete(avl);
    }

    printf("success!\n");

    rc = 0;
fail:
    kuan_array_delete(ka);
    if (avl)
        avl_delete(avl);
    return rc;
}

int main(int argc, char **argv)
{
    if (argc > 2)
        return _arg(argc, argv);
     else
        return _array(atoi(argv[1]));
}
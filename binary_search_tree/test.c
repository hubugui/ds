#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int
main(int argc, char **argv) {
    int i;
    struct bst *t = bst_new();

    if (!t) {
        printf("bst_new() fail\n");
        return -1;
    }

    for (i = 1; i < argc - 2; i++) {
        if (bst_insert(t, atoi(argv[i]))) {
            printf("bst_insert() fail\n");
            goto fail;
        }
    }

    bst_dump(t);

    if (bst_search(t, atoi(argv[argc - 2])) == 0)
        printf("%s exist.\n", argv[argc - 2]);
    else
        printf("%s not exist.\n", argv[argc - 2]);
        
    if (bst_remove(t, atoi(argv[argc - 1])) == 0)
        printf("%s remove success.\n", argv[argc - 1]);
    else
        printf("%s remove fail.\n", argv[argc - 1]);

    bst_dump(t);

fail:
    bst_delete(t);
    return 0;
}

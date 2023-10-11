#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int approach_1(void);
int approach_2(void);
int approach_3(void);

int main(void)
{
    approach_1();
    approach_2();
    approach_3();
}

int approach_1(void)
{
    int list[3];

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    for (int i = 0; i < 3; i++) {
        printf("%i: %i\n", i, list[i]);
    }

    return 0;
}

int approach_2(void)
{
    int *list = malloc(3 * sizeof(int));
    assert(list != NULL);

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // ...

    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL) {
        free(list);
    }

    for (int i = 0; i < 3; i++) {
        tmp[i] = list[i]; // Copying from |1|2|3| to |~|~|~|~|
    }
    tmp[3] = 4;
    free(list);

    list = tmp;

    for (int i = 0; i < 4; i++) {
        printf("%i: %i\n", i, list[i]);
    }

    free(list); // Now list holds garbage values
                // NOTE: free(tmp) also does the same thing, but isn't
                // responsible in regards to ownership semantics and well
                // designed code

    return 0;
}

int approach_3(void)
{
    int *list = malloc(3 * sizeof(int));
    assert(list != NULL);

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // ...

    /*
     * memory leak can happen if realloc is pointed to list, instead of a
     * temporary pointer
     * list = realloc(list, 4 * sizeof(int));
     * OR
     * realloc(list, 4 * sizeof(int));
     */
    int *tmp
        = realloc(list, 4 * sizeof(int)); // NOTE: realloc automatically frees
                                          // the previous memory for you
    if (tmp == NULL) {
        free(list);
        return 1;
    }

    /*
     * We don't need a for loop to manually copy from tmp to list,
     * just point the start item's address of list to tmp
     */
    list = tmp;

    list[3] = 4;

    for (int i = 0; i < 4; i++) {
        printf("%i: %i\n", i, list[i]);
    }

    free(list);

    return 0;
}

/*

Here from data_structures.c

# resizing arrays

go to linked_list.c

*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// No nneed to copy all the time with self referencing,
// but with a downsides:
// - storing next pointer address values.
//   even though int are 4 bytes and addr is 8 bytes.
// - can't index into linked list, as they have are stored apart with
//   big gaps in CPU's memory layout.
//   e.g. binary search not possible with indexing
typedef struct node {
    int number;
    struct node *next; // Can now self refereence
                       // node *next; // Unknown type name.
} node;

int approach_1(void);
int approach_2(int argc, char **argv);
int approach_3(void);

int main(int argc, char **argv)
{
    assert(approach_1() == 0);
    assert(approach_2(argc, argv) == 0);
    // assert(approach_3() == 0);

    return 0;
}

int approach_1(void)
{
    node *list = NULL; // OR `void *list;`

    node *n = malloc(sizeof(node));
    if (n == NULL)
        return 1;
    /*
     * (*n) star n, dereference n, follow the arrow to memory of number put
     *      there with ....(.number), also (.next] holds garbage value pointing
     *      who knows where malloc, realloc will assign 0 to it.
     */
    (*n).number = 1;
    (*n).next = NULL;

    n->number = 1;
    n->next = NULL;

    list = n; // now list of sizeof(1) exist pointing to first node
    //
    // Using scope for demonstration to avoid clashing `n` identifier
    {
        // malloc allocates two rectangular memory address anywhere
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            free(list); // cleanup previous allocation to tmp n via list
            return 1; // EXIT_FAILURE
        }
        n->number = 2;
        n->next = NULL; // Get rid of second garbage value allocated by malloc
        // list = n;    // AVOID: loses pointer to original node and orphans it
        n->next = list; // Point it to first node
        list = n; // list takes ownership from the temporary node *n to avoid
                  // redundancy of 2 ptrs to first node
        /* list -> 2 -> 1 -> NULL */
        // Using scope for demonstration to avoid clashing `n` identifier
        {
            // ... keep prepending more
            /* For example; list -> 3 -> 2 -> 1 -> NULL */
        }
    }
    assert(list != NULL);
    assert(list->number == 2);
    assert(list->next != NULL);
    assert(list->next->number == 1);
    assert(list->next->next == NULL);
    // ... if prepended more nodes, keep checking...

    // ... if prepended more nodes, free nested nodes free(list->next->next);
    if (list != NULL) {
        // ...
        if (list->next != NULL)
            free(list->next);
        free(list);
    }

    return 0;
};

int approach_2(int argc, char **argv)
{
    // list: 0x4a44180 list->number: 0x4a44180 list->next: 0x4a44188
    node *list = NULL;

    // i is 1 as 0 is name of the executable program.
    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return 1; // or break and free
        }
        n->number = number;
        n->next = NULL;

        n->next = list;
        list = n;
    }

    node *ptr = list;
    while (ptr != NULL) {
        printf("ptr->number: %i \n", ptr->number);
        ptr = ptr->next;
    }
    ptr = list; // reset ptr position to point to list gead/root

    while (ptr != NULL) {
        node *nxt = ptr->next;
        free(ptr);
        ptr = nxt;
    }
    assert(ptr->next == NULL);
    assert(ptr == NULL);

    return 0;
}
// clang-format off
/*

Here from list.c

# Linked Lists

How to stitch these 3 values together?

|        |        | 1      |        |        |        |        |        |
|        |        |        |        | 2      |        |        |        |
|        |        |        |        |        |        | 3      |        |

Allocate more memory beside them that hold the address to the next

|        |        |1  0x123|        |        |        |        |        |
|        |        |0x456   |        |2  0x456|        |        |        |
|        |        |        |        |0x789   |        |3  0x789|        |
|        |        |        |        |        |        |?       |        |

|        |        |1  0x123|        |        |        |        |        |
|        |        |0x456   |        |2  0x456|        |        |        |
|0x123   |        |        |        |0x789   |        |3  0x789|        |
|        |        |        |        |        |        |NULL    |        |

root node ptr points to 1 at 0x123
next of last node 3 points to NULL, signifying end of linked list
the rectagular data is a node. it has value and next ptr

A single linked list

root ->  1    ->   2   ->   3    ->  NULL
0x123    0x457     0x789    0x0

# Time Complexity: running time of linked list
> (pre)pend (a)pend # pre after # start end

seaching  : O(n) // prepend
seaching  : O(n) // append
insertion : O(1) // prepend
insertion : O(n) // append: naive approach: have to traverse the whole tree
                 //         optimized: have a ptr for last node or back
sorting   : O(n)

go to tree.c

*/
// clang-format on

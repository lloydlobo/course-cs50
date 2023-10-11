#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int err_t;

/** Use `err_t` of type `int` as `err_` return type */
enum err_ {
    ErrOk = 0, // "(no error)"
    ErrNoMem = -12, // "failed to allocate memory"
};

struct node {
    int number;
    struct node *left;
    struct node *right;
};

struct node *tree_init(int num);
struct node *tree_from_list(struct node *mut_self, int *array, int size);
err_t tree_add_l(struct node *mut_self, int lnum);
err_t tree_add_r(struct node *mut_self, int rnum);
bool tree_search_bst(struct node *self, int num);
void tree_print(struct node *self);
void tree_free(struct node *self);

int main(void)
{
    int arr[] = { 2, 1, 3 };
    int arr_counter = 0;

    struct node *tree = tree_init(arr[arr_counter++]);

    if (tree_add_l(tree, arr[arr_counter++]) != 0) {
        return EXIT_FAILURE;
    };
    if (tree_add_r(tree, arr[arr_counter++]) != 0) {
        return EXIT_FAILURE;
    };

    assert(tree != NULL);
    assert(tree_search_bst(tree, arr[0]) == true);

    tree_print(tree); // 1
                      // 2
                      // 3
    tree_free(tree);

    return EXIT_SUCCESS;
}

/**
 * # Error
 * - panics on memory allocation error
 */
struct node *tree_init(int num)
{
    struct node *self = malloc(sizeof(struct node));
    assert(self != NULL);
    self->number = num;
    self->left = NULL;
    self->right = NULL;

    return self;
}

void tree_free(struct node *self)
{
    if (self == NULL)
        return;
    tree_free(self->left);
    tree_free(self->right);
    free(self);
}

void tree_print(struct node *self)
{
    if (self == NULL)
        return;
    tree_print(self->left);
    printf("%i\n", self->number);
    tree_print(self->right);
}

/**
 * # Error
 * - panics if NULL node is passed
 */
err_t tree_add_l(struct node *mut_self, int lnum)
{
    assert(mut_self != NULL);

    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        tree_free(mut_self);
        return ErrNoMem;
    }
    n->number = lnum;
    n->left = NULL;
    n->right = NULL;
    mut_self->left = n;

    return ErrOk;
}

/**
 * # Error
 * - panics if NULL node is passed
 */
err_t tree_add_r(struct node *mut_self, int rnum)
{
    assert(mut_self != NULL);

    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        tree_free(mut_self);
        return ErrNoMem;
    }
    n->number = rnum;
    n->left = NULL;
    n->right = NULL;
    mut_self->right = n;

    return ErrOk;
}

/**
 * Return true if number is found in binary search tree (BST)
 *
 * Tradeoffs:
 * - uses lots of memory
 * - no tail call optimization
 * - function call overhead
 */
bool tree_search_bst(struct node *tree, int num)
{
    if (tree == NULL)
        return false;
    else if (num < tree->number)
        return tree_search_bst(tree->left, num);
    else if (num > tree->number)
        return tree_search_bst(tree->right, num);

    return true;
}

// clang-format off
/*

Here from linked_list.c

# Binary search tree (BST)

Imagine then that the center value becomes the top of a tree. Those that
are less than this value are placed to the left. Those values that are
more than this value are to the right.

left<-  root   ->right
         4
   2           6
1     3     5     7

Pointers can then be used to point to the correct location of each area
of memory such that each of these nodes can be connected.

# BST unfortunate perversion into linked list

Height wont be in log(n) (base 2) if its not balanced,
can devolve into O(n) if its unbalaced.

         1
               2
                  3

// ...

go to dictionary.c

*/
// clang-format on

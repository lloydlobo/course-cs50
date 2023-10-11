#include <stdio.h>

int main(void)
{
    printf("Hello, data structures\n");

    return 0;
}

/*

# queue

enqueue - adding to end of queue
dequeue - first item to go through the queue is popped

# stack

LIFO
FIFO
gmail is type of stack
a stack of plates

# problem with fixed/static stack size

```C
const int CAPACITY = 50;

typedef struct {
    person people[CAPACITY];
    int size;
} stack;
```

# resizing arrays

|1|2|3|

to add 4 to stack the next contiguous memory address is picked
|1|2|3| |

but, what if it is occupied?
|~|~|~|~|~|~|~|~|
|~|1|2|3|h|e|l|l|
|o|,| |w|o|r|l|d|
|\0|~|~|~|~|~|~|~|

Hypothetical approach to solve the above
copy array somewhere else that has enough space or garbage values
but, it takes a lot of copying if this becomes the norm

but we can do better.
go to list.c

*/

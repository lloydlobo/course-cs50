#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define BOOL bool;

void print_line(void) { printf("————————————————————————————\n"); }

void err_argv_len_not_enough(void) {
  printf("err: No arguments were entered.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void err_argv_len_more_than_expected(void) {
  printf("Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void err_argv_1_key_not_int(void) {
  printf("err: Entered key is not a valid positive integer.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_2_not_a_string(void) {
  printf("err: Entered password is not a valid text.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

// https://stackoverflow.com/questions/5904530/how-do-header-and-source-files-in-c-work
/* Converting C source code files to an executable program is normally done in
two steps: compiling and linking.

First, the compiler converts the source code to object files (*.o). Then, the
linker takes these object files, together with statically-linked libraries and
creates an executable program.

In the first step, the compiler takes a compilation unit, which is normally a
preprocessed source file (so, a source file with the contents of all the headers
that it #includes) and converts that to an object file.

In each compilation unit, all the functions that are used must be declared, to
let the compiler know that the function exists and what its arguments are. In
your example, the declaration of the function returnSeven is in the header file
header.h. When you compile main.c, you include the header with the declaration
so that the compiler knows that returnSeven exists when it compiles main.c.

When the linker does its job, it needs to find the definition of each function.
Each function has to be defined exactly once in one of the object files - if
there are multiple object files that contain the definition of the same
function, the linker will stop with an error.

Your function returnSeven is defined in source.c (and the main function is
defined in main.c).

So, to summarize, you have two compilation units: source.c and main.c (with the
header files that it includes). You compile these to two object files: source.o
and main.o. The first one will contain the definition of returnSeven, the second
one the definition of main. Then the linker will glue those two together in an
executable program.

About linkage:

There is external linkage and internal linkage. By default, functions have
external linkage, which means that the compiler makes these functions visible to
the linker. If you make a function static, it has internal linkage - it is only
visible inside the compilation unit in which it is defined (the linker won't
know that it exists). This can be useful for functions that do something
internally in a source file and that you want to hide from the rest of the
program.

Share */

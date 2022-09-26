// $ cc example.c -o example -lm
// Compile binary with `-lm` flag, when linking the math lib.
// $ ls *.c | entr gcc y2k.c -o y2k -lm
// $ ls *.c | entr gcc y2k.c -o y2k -lm -v
// `-v` for verbose output logging.
#include <math.h>

#include <stdio.h>

int pennies();
/*
 * It was the year: 1999
 * Computers with limited memory due to expensive hardware,
 * stored year in double digits. And had to change the year to 2000.
 * 99
 * +1
 * 00   bit overflows....
 * Instead of 2000
 * Programmers back then warded it off by writing lots of code in `old`
 * languages. Clocks might break again. 19 January 2038 Computer track time by
 * calculating total no. of secods defined by the `epoch` => January 1, 1970.
 * Good year to start off when Computers came on to the scene.
 * 2 Billion - 4 billion capacity. -2 billion < bits > +2 billion
 * 32 bits. 2147483647
 * rollsoff 011111111111111111111111111111111111
 *                                             1
 * rollsoff 011111111111111111111111111111111110
 * rollsoff 011111111111111111111111111111111100
 * ...
 * rollsoff 100000000000000000000000000000000000  // Negative number
 * Computer will think its 13 December 1901.
 * More bits is the solution. 64 bits.
 * We'll be long gone for 64 bits equivalent of seconds.
 */

int main(int argc, char *argv[]) {
  int p = pennies();
  printf("Pennies: %i\n", p);

  return 0;
}

// Use round func with math lib.
//
// Calculate dollars to pennies.
// Imprecision.
// amount: 4.20
// Pennies: 419
// $4 & 19.9999 cents
int pennies() {
  float amount;

  printf("amount: ");
  scanf("%f", &amount);

  // <math.h> for round || roundf ==> functions
  // The functions in stdlib.h and stdio.h have implementations in libc.so (or
  // libc.a for static linking), which is linked into your executable by default
  // (as if -lc were specified).
  return roundf(amount * 100);
}

/*
 * $~ y2k.c:(.text+0x9f): undefined reference to `roundf'
 *
 * https://stackoverflow.com/questions/31465289/undefined-reference-to-roundf-c-language
 * link with the math library:
 *
 * $ cc example.c -o example -lm
 *
 * The math library functions are not part of standard C library which is linked
 * by default. So you need link it yourself. There's an interesting thread about
 * why it's not part of libc: Why do you have to link the math library in C?
 *
 * https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c
 * So if your program is using math functions and including math.h, then you
 * need to explicitly link the math library by passing the -lm flag. The reason
 * for this particular separation is that mathematicians are very picky about
 * the way their math is being computed and they may want to use their own
 * implementation of the math functions instead of the standard implementation.
 * If the math functions were lumped into libc.a it wouldn't be possible to do
 * that.
 *
 * The functions in stdlib.h and stdio.h have implementations in libc.so (or
 * libc.a for static linking), which is linked into your executable by default
 * (as if -lc were specified). GCC can be instructed to avoid this automatic
 * link with the -nostdlib or -nodefaultlibs options. The math functions in
 * math.h have implementations in libm.so (or libm.a for static linking), and
 * libm is not linked in by default. There are historical reasons for this
 * libm/libc split, none of them very convincing. Interestingly, the C++ runtime
 * libstdc++ requires libm, so if you compile a C++ program with GCC (g++), you
 * will automatically get libm linked in.
 */

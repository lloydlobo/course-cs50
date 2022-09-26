#include <stdio.h>

int main(void) {
  int *x;
  int y;
  // Prompt user for x.
  printf("x: ");
  scanf("%i", x);

  // Prompt user for y.
  printf("y: ");
  scanf("%i", &y);

  // Perform division.
  float div = *x / (float)y; // (float) x / (float)y;
  printf("division: %.50f\n", div);

  // Perform addition.
  float add = *x + y;
  printf("addition: %.50f\n", add);

  return 0;
}

// Truncation. (Solved with typee conversion)
// int / int => C throws away everything after decimal floating point.
// Convert y to float by casting y to a float with `(float) y`.
// Usage: Only once in an operation is enough.
//
// Floating Point Imprecision.
//
// Integer/ Float bits overflow approximation.
// Finite memory computer can't possibly approx.
//
// x: 1
// y: 10
// division: 0.10000000149011611938476562500000000000000000000000
// addition: 11.00000000000000000000000000000000000000000000000000

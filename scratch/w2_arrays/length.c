/* [[file:../../README.org::w2_arrays/length.c][w2_arrays/length.c]] */
//
// https://manual.cs50.io/
#include <stdio.h>
#include <string.h>

// int string_len(char[8]);
int str_len(char[8]);

// strlen() manual implementation.
int main(int argc, char *argv[]) {
  char name[] = "Gandalf";

  int out_strlen = strlen(name);   // standard library function.
  int out_str_len = str_len(name); // manual helper function.

  printf("| strlen: %i | str_len: %i\n", out_strlen, out_str_len);

  return 0;
}

// /* Return the length of S.  */
// extern size_t strlen (const char *__s)
//      __THROW __attribute_pure__ __nonnull ((1));
int str_len(char *s) {
  int i = 0;

  // Scan each char at i for NUL `\0`.
  while (s[i] != '\0') {
    // If it is not NUL increment the counter i.
    i++;
  }

  return i;
}

// int len = string_len(name);
// int string_len(char[8] s) {}
//
/* w2_arrays/length.c ends here */

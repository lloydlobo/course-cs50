// https://manual.cs50.io/
#include <stdio.h>

// int string_len(char[8]);
int str_len(char[8]);

// strlen() manual implementation.
int main(int argc, char *argv[]) {
  char name[] = "Gandalf";

  int strlen = str_len(name);

  printf("strlen: %i\n", strlen);

  return 0;
}

//  Passing arguments to 'str_len' without
// a prototype is deprecated in all versions
// clang(-Wdeprecated - non - prototype)[10, 23]
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

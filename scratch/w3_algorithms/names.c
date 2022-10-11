#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *names[] = {"Bill", "Charlie", "Ron"};
  int n = strlen(*names) - 1;
  for (int i = 0; i < n; i++) {
    // if return val is 0 or same.
    // docs recommend for checking for 0.
    if (strcmp(names[i], "Hermione") == 0) {
      printf("Found: %s\n", names[i]);
      return EXIT_SUCCESS;
    }
  }
  printf("Not found\n");
  return EXIT_FAILURE;
}

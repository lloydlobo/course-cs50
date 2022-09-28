#include <stdio.h>

int main(int argc, char *argv[]) {
  // CLI input has 2 arguments.
  // $ ./filename <string>
  if (argc == 2) {
    printf("%s\n", argv[1]); // Print the user argv.
    return 0;                // Exit status 0 (success).
  }

  // Else handle user error & inform
  printf("Error: Please enter a valid argv flag.\n\n");
  printf("Usage:\n");
  printf("      ./argv <word> | ./argv hello\n");

  return 1; // Exit status 1 (error).
}

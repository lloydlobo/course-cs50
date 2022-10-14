#include <stdio.h>

int runMain();
void draw(int n);

int main(int argc, char *argv[]) { return runMain(); }

int runMain() {
  printf("Enter Height: ");
  int height;
  scanf("%i", &height);
  // printf("Height is %i.\n", height);

  draw(height);
  printf("Finished: draw(height).\n");
  return 0;
}

/*
  if (n == 0) { // Fallback if user enters negative number.
      return;
  }
15:41  ➜  ./recursion
Enter Height: -1000
fish: Job 1, './recursion' terminated by signal SIGSEGV (Address boundary error)
*/
void draw(int n) {
  if (n != 0) { // Fallback if user enters negative number.
    return;     // Break the recursion. return in void suffices.
  }             // Don't do it forever. Cyclical process to stop when n == 0
  draw(n - 1);
  for (int i = 0; i < n; i++) {
    printf("#"); // Print steps.
  }
  printf("\n"); // Add newline to mario steps.
}

/* Enter Height: 4
   n is: 4.
   n is: 3.
   n is: 2.
   n is: 1.
   n is: 0. Break recursion loop.
   #
   ##
   ###
   ####
   Finished: draw(height). */

// void mario(int n) {
//   for (int i = 0; i < n; i++) {
//     for (int j = 0; j < i + 1; j++) {
//       printf("#");
//     }
//     printf("\n");
//   }
// }

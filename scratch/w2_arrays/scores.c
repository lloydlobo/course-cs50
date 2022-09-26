/* [[file:../../README.org::w2_arrays/scores.c][w2_arrays/scores.c]] */
#include <stddef.h>
#include <stdio.h>

void scores(void);
void scores_array(void);
int prompt_score(int);
int prompt_total_scores();
float scores_array_prompt(void);

// TODO close while loop when -ve num is entered.
// int negative_int(void);
int main(int argc, char *argv[]) {
  printf("~scores.c~\n");

  scores();
  scores_array();
  float avg = scores_array_prompt();

  printf("\nAverage: %.2f\n", avg);
  // int n_main = negative_int();
  // printf("negative_int: %i\n", n_main);
  return 0;
}

// scores returns average of scores.
//
// As long as one arg in an operation is a float.
// it returns float.
//
// dont't hardcode avg denominator.
void scores(void) {
  int s1 = 72;
  int s2 = 73;
  int s3 = 33;

  // ### variable `array`
  int scores[3] = {s1, s2, s3};

  float avg = ((float)s1 + s2 + s3) / 3; // or use 3.0;

  printf("Average: %.2f\n", avg);
}

// ### `expression`
// Type: `unsigned long`
// int scores[3] = {72, 73, 33};
void scores_array(void) {
  const int len = 3; // allocate capacity og scores array.
  int scores[len];   // ### variable `array`
  int sum;           // scores[0] + scores[1] + scores[2]
  float avg;         // scores sum / scores size

  scores[0] = 72;
  scores[1] = 73;
  scores[2] = 33;

  for (int i = 0; i < len; i++) {
    int score = scores[i]; // printf("\n%2i: score: %i\n", i, score);
  }

  sum = (scores[0] + scores[1] + scores[2]);
  avg = sum / (float)len;

  printf("\nAverage_Array: %.2f\n\n\n", avg);
}

//   Format specifies type 'int *' but the argument has type 'int' clang
// (-Wformat) [79, 15]
int prompt_score(int idx) {
  int score;

  printf("Enter a score(%i): ", idx + 1);
  scanf("%i", &score);

  return score;
}

int prompt_total_scores() {
  int length;

  printf("How many scores? ");
  scanf("%i", &length);

  return length;
}

/*
 * ! Code Smell
 *
 * int scores[3] = {72, 73, 33};
 * OR
 * scores[0] = prompt_user();
 * scores[1] = prompt_user();
 * scores[2] = prompt_user();
 *
 */

// scores_array_prompt returns average of user input scores.
//
// Initialize `prev` to 0 to avoid errors.
float scores_array_prompt(void) {
  int len = prompt_total_scores(); // Allocate capacity of scores array.
  int s[len];                      // Initialize array with capacity len.

  int prev = 0; // Previous cached sum.
  int curr;     // Current score being looped.
  int sum;      // s[0] + s[1] + s[2].

  for (int i = 0; i < len; i++) {
    s[i] = prompt_score(i); // Prompt user for int & store in ith pos.

    curr = prev + s[i]; // Add prev sum and current prompted score.

    sum = curr; // Assign sum to curr value.
    prev = sum; // Reset prev to sum.
  }

  return sum / (float)len; // Assert float type once.
}

// USE `STEP INTO` IN THE DEBUGGER MENU (F11) (down arrow)
// negative_int returns a negative integer.
int negative_int(void) {
  int n = -1;

  // Err: while loop won't wui when -ve int is entered.
  do {
    /* Prompt integer from user. */
    printf("Enter negative integer: ");

    scanf("%i", &n); // Doesn't work when neg < 0 => so debug.
    printf("negative int: %i\n\n", n);
  } while (n < 0);

  return n;
}
/* w2_arrays/scores.c ends here */

#include <ctype.h>
#include <math.h> // add `-lm` flag while compiling.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL bool;

/*
 * It's in the standard library, and that's the most straight forward way
 * I can see to implement such a function. So yes, just loop through the
 * string and convert each character to lowercase.
 *
 * Something trivial like this:
 */
/* for(int i = 0; str[i]; i++){
  str[i] = tolower(str[i]);
} */
/*
 * or if you prefer one liners, then you can use this one by J.F.
 * Sebastian:
 */
// for ( ; *p; ++p) *p = tolower(*p);
/* [Earlz] [so/q/2661766] [cc by-sa 3.0] */

void prompt(void);
// char *round_it(float f);

const char *STR = "One fish. Red fish. Blue fish. Yellow fish.";
const float PER_100_WORDS = 100.0;
const char SPACE = 32;
const char PERIOD = '.';
const char EXCLAMATION = '!';

int main(int argc, char *argv[]) {
  int malloc;
  malloc = strlen(STR); // allocate memory by SRL strlen size.

  const int MALLOC = 100;
  const int MALLOC_OUT = 16;
  const char *string_user[MALLOC]; // const char *str[malloc];

  int string_count = 0;
  int letter_count = 0;
  int word_count;
  int sentence_count;

  int word_counter = 1;
  int sentence_counter = 0;

  /* assign string string count. */

  // TODO: Remove this later. For direct len calculation.
  // string_count = strlen(STR);
  for (int i = 0; i < MALLOC + 1; i++) {
    string_user[i] = &STR[i];
  }
  string_count = strlen(*string_user);

  /* lower string count. */

  // NOTE: Do we need lower case string?
  char str[string_count]; // Declare array to copy lower string.

  for (int i = 0; i < string_count + 1; i++) {
    int c = STR[i];
    char l = tolower(c);
    bool is_between_a_z = l >= 97 && l <= 122;

    str[i] = l;
    if (is_between_a_z) {
      letter_count++;
    }
  }

  /* word count. */

  for (int i = 0; i < string_count; i++) {
    char c = *string_user[i];
    if (c == SPACE) {
      word_counter++;
    }
  }
  word_count = word_counter;

  /* sentence count. */

  for (int i = 0; i < string_count; i++) {
    char c = *string_user[i];
    if (c == PERIOD || c == EXCLAMATION) {
      sentence_counter++;
    }
  }
  sentence_count = sentence_counter;

  /* Average Count */

  float letter_avg = ((float)(letter_count) / word_count) * PER_100_WORDS;
  float sentence_avg = ((float)(sentence_count) / word_count) * PER_100_WORDS;

  /* Coleman-Liau Index */

  // grade := 0.0588*l - 0.296*s - 15.8
  float calculate_grade =
      roundf(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8);

  char sprint_grade[MALLOC];

  if (calculate_grade <= 1) {
    for (int i = 0; i <= MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Before Grade 1");
    }
  } else if (calculate_grade <= 16) {
    for (int i = 0; i >= MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Grade 16+");
    }
  } else {
    for (int i = 0; i < MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Grade %g", calculate_grade);
    }
  }

  /* Print results. */

  char f_out[MALLOC];
  for (int i = 0; i <= MALLOC; i++) {
    f_out[i] = sprintf(f_out, "Text: %s\n%s", STR, sprint_grade);
  }

  printf("%s\n\n", str);
  printf("word_count:       %i\n", word_count);
  printf("letter_count:     %2i\n", letter_count);
  printf("sentence_count:   %i\n", sentence_count);
  printf("l_avg:            %.2f\n", letter_avg);
  printf("s_avg:            %.2f\n", sentence_avg);
  printf("calculate_grade:  %.2f\n", calculate_grade);
  printf("sprint_grade:     %2s\n", sprint_grade);

  printf("\n%s\n", f_out);

  return 0;
}

void prompt(void) {
  // printf("Enter Text\n");
  // fgets(name, sizeof(name), stdin); // read string.
  // printf("\nHello "); // print prefix.
  // puts(name);         // Write a string, followed by a newline, to stdout.
}
// for (int i = 0; i < strlen(msg_1); i++) { out[i] = msg_1[i]; }

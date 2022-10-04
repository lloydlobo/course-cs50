#include <ctype.h>
#include <math.h> // add `-lm` flag while compiling.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL bool;

/*
 * CONSTANTS.
 */
const int MALLOC = 100;
const int MALLOC_OUT = 16;
const float PER_100_WORDS = 100.0;
const char SPACE = 32;
const char PERIOD = '.';
const char EXCLAMATION = '!';
const char QUESTION = '?';

/*
 * Forward declaration for functions.
 */
void prompt(void);
const char *get_testcases(); // Without prototype.

/*
 * Entry point function main().
 */
int main(int argc, char *argv[]) {
  const char *INPUT_STR = get_testcases();
  const char *string_user[MALLOC]; // const char *str[malloc];
  int malloc = strlen(INPUT_STR);  // allocate memory by SRL strlen size.

  int string_count = 0;
  int letter_count = 0;
  int word_count = 1;
  int sentence_count;

  /* assign string count. */

  for (int i = 0; i < MALLOC + 1; i++) {
    string_user[i] = &INPUT_STR[i];
  }
  string_count = strlen(*string_user);

  /* lower string count. */

  char str[string_count]; // Declare array to copy lower string.

  for (int i = 0; i < string_count + 1; i++) {
    int c = INPUT_STR[i];
    char l = tolower(c);
    bool is_between_a_z = l >= 97 && l <= 122;

    str[i] = l;
    if (is_between_a_z) {
      letter_count++;
    }
  }

  /* word count. */

  for (int i = 0; i < string_count; i++) {
    char *c = &str[i];
    if (*c == SPACE) {
      word_count++;
    }
  }

  /* sentence count. */

  for (int i = 0; i < string_count; i++) {
    // char c = *string_user[i];
    char c = str[i];
    if (c == EXCLAMATION || c == QUESTION || c == PERIOD) {
      sentence_count++;
    }
  }

  /* Average Count */

  float letter_avg = ((float)(letter_count) / word_count) * PER_100_WORDS;
  float sentence_avg = ((float)(sentence_count) / word_count) * PER_100_WORDS;

  /* Coleman-Liau Index */

  float calculate_grade = roundf(0.0588 * letter_avg - 0.296 * sentence_avg -
                                 15.8); // grade := 0.0588*l - 0.296*s - 15.8

  char sprint_grade[MALLOC];

  if (calculate_grade <= 1) {
    for (int i = 0; i <= MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Before Grade 1");
    }
  } else if (calculate_grade >= 16) {
    for (int i = 0; i >= MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Grade 16+");
    }
  } else {
    for (int i = 0; i < MALLOC_OUT; i++) {
      sprint_grade[i] = sprintf(sprint_grade, "Grade %g", calculate_grade);
    }
  }

  printf("%s\n\n", str);
  printf("word_count:       %i\n", word_count);
  printf("letter_count:     %2i\n", letter_count);
  printf("sentence_count:   %i\n", sentence_count);
  printf("l_avg:            %.2f\n", letter_avg);
  printf("s_avg:            %.2f\n", sentence_avg);
  printf("calculate_grade:  %.2f\n", calculate_grade);
  printf("sprint_grade:     %2s\n", sprint_grade);

  /* Print results. */

  // TODO:
  // FIX: this. It disrupts all the printf above.
  // char f_out[MALLOC];
  // for (int i = 0; i <= MALLOC; i++) {
  //   f_out[i] = sprintf(f_out, "Text: %s\n%s", INPUT_STR, sprint_grade);
  // }
  // printf("\n%s\n", f_out);

  return 0;
}

void prompt(void) {
  // printf("Enter Text\n");
  // fgets(name, sizeof(name), stdin); // read string.
  // printf("\nHello "); // print prefix.
  // puts(name);         // Write a string, followed by a newline, to stdout.
}
// for (int i = 0; i < strlen(msg_1); i++) { out[i] = msg_1[i]; }

/*
 * get_testcases function returns a string to grade.
 */
const char *get_testcases() {
  const char *STR_1 = "One fish. Two fish. Red fish. Blue fish.";
  const char *STR_2 =
      "Would you like them here or there? I would not like them "
      "here or there. I would not like them anywhere.";
  const char *STR_3 = "Congratulations! Today is your day. You're off to Great "
                      "Places! You're off and away!";
  const char *STR_5 =
      "Harry Potter was a highly unusual boy in many ways. For one thing, he "
      "hated the summer holidays more than any other time of year. For "
      "another, "
      "he really wanted to do his homework, but was forced to do it in "
      "secret, "
      "in the dead of the night. And he also happened to be a wizard.";
  const char *STR_7 =
      "In my younger and more vulnerable years my father gave me some advice "
      "that I've been turning over in my mind ever since.";
  const char *STR_8_0 =
      "Alice was beginning to get very tired of sitting by her sister on the "
      "bank, and of having nothing to do: once or twice she had peeped into "
      "the "
      "book her sister was reading, but it had no pictures or conversations "
      "in "
      "it, \"and what is the use of a book,\" thought Alice \"without "
      "pictures "
      "or conversation?\"";
  const char *STR_8_1 =
      "When he was nearly thirteen, my brother Jem got his arm badly broken "
      "at "
      "the elbow. When it healed, and Jem's fears of never being able to "
      "play "
      "football were assuaged, he was seldom self-conscious about his "
      "injury. "
      "His left arm was somewhat shorter than his right; when he stood or "
      "walked, the back of his hand was at right angles to his body, his "
      "thumb "
      "parallel to his thigh.";
  const char *STR_9 =
      "There are more things in Heaven and Earth, Horatio, than "
      "are dreamt of in your philosophy.";
  const char *STR_10 =
      "It was a bright cold day in April, and the clocks were striking "
      "thirteen. "
      "Winston Smith, his chin nuzzled into his breast in an effort to "
      "escape "
      "the vile wind, slipped quickly through the glass doors of Victory "
      "Mansions, though not quickly enough to prevent a swirl of gritty dust "
      "from entering along with him.";
  const char *STR_16 =
      "A large class of computational problems involve the determination of "
      "properties of graphs, digraphs, integers, arrays of integers, finite "
      "families of finite sets, boolean formulas and elements of other "
      "countable "
      "domains.";

  return STR_3;
}

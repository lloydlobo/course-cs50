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
const int MALLOC = 240;
const int MALLOC_OUT = 16;
const float PER_100_WORDS = 100.0;
const char SPACE = 32;
const char PERIOD = '.';
const char EXCLAMATION = '!';
const char QUESTION = '?';

/*
 * Forward declarations for functions.
 */
const char *prompt_text(void);
const char *get_testcases(); // Without prototype.

int get_count_s(char s[MALLOC]) {
  printf("void print_s: %s\n", s);

  /* Subtract the last escape char or NUL maybe. */

  int count_input = strlen(s);
  count_input--;

  return count_input;

} // printf("strlen input: %i\n", count_input);

int count_words(char str[MALLOC], int str_count) {
  int counter = 1; // Set atleast one word pre loop.
  for (int i = 0; i < str_count; i++) {
    if (str[i] == SPACE) {
      counter++;
    }
  }
  return counter;
}

// char curr = str[i]; bool is_end = curr == PERIOD || curr == QUESTION ||
// curr == EXCLAMATION;
//   if (is_end) {
//   char prev = str[i - 1];
//   if (prev == QUESTION || prev == EXCLAMATION) { counter++; }
//    else if (curr == PERIOD) { counter++; }
// }
int count_sentences(char str[MALLOC], int str_count) {
  int counter = 0; // TODO: Set atleast one sentence pre loop.
  for (int i = 0; i < str_count; i++) {
    char c = str[i];
    bool is_line_end = i == str_count - 1 && counter == 0;
    bool is_curr_sentence_end =
        c == PERIOD || c == QUESTION || c == EXCLAMATION;
    if (c == EXCLAMATION || c == QUESTION || c == PERIOD) {
      counter++;
      // if (is_line_end) {
      //   counter++; // Fallback for 1 sentence text.
      // }
    }
  }
  return counter;
}

int count_letters(char str[MALLOC], int str_count) {
  int counter = 0; // Set atleast one word pre loop.
  for (int i = 0; i < str_count; i++) {
    char c = tolower(str[i]);
    bool is_lower_a_to_z = c >= 97 && c <= 122;
    if (is_lower_a_to_z) {
      counter++;
    }
  }
  return counter;
}

float average_sentences(float s_len, float w_len) {
  return ((float)s_len / w_len) * PER_100_WORDS;
}

float average_letters(float l_len, float w_len) {
  return ((float)l_len / w_len) * PER_100_WORDS;
}

/*
 * coleman_liau_index calculates grade of a text.
 *
 * grade := 0.0588*l - 0.296*s - 15.8
 */
float coleman_liau_index(float letter_avg, float sentence_avg) {
  return roundf(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8);
}

/*
 * Entry point function main().
 */
int main(int argc, char *argv[]) {
  const char *INPUT_STR = get_testcases();
  const char *string_user[MALLOC]; // const char *str[malloc];

  /* prompt user for text. */

  char s[MALLOC]; // NOTE: Prompt Text from user.
  printf("Enter text to grade with Coleman-Liau formulat:\n");
  fgets(s, sizeof(s), stdin);
  printf("\nInput: %s\n", s);
  puts(s); // Write a string, followed by a newline, to stdout.

  int s_count = get_count_s(s);

  /* assign string, word, sentences, letters count. */

  int w_len = count_words(s, s_count);
  int s_len = count_sentences(s, s_count);
  int l_len = count_letters(s, s_count);
  printf("%i, %i, %i\n", w_len, s_len, l_len);

  /* calculate average letter & sentence count / 100 words. */

  float s_avg = average_sentences(s_len, w_len);
  float l_avg = average_letters(l_len, w_len);
  printf("%.2f, %.2f\n", l_avg, s_avg);

  /* Calculate Coleman-Liau Index Grade. */

  float cli_grade = coleman_liau_index(l_avg, s_avg);
  printf("cli_grade: %f\n", cli_grade);

  /* assign string count. */

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

/*
 * prompt_text function gets input text from the stdin..
 * And then puts it into a variable.
 */
const char *prompt_text(void) {
  char input_str[MALLOC];
  printf("Enter Text:\n");
  fgets(input_str, sizeof(input_str),
        stdin); // Get a newline-terminated string of finite length from STREAM.
  puts(input_str); // Write a string, followed by a newline, to stdout.

  int input_len;
  for (int i = 0; i < strlen(input_str); i++) {
    if (input_str[i] != '\0') {
      input_len++;
    }
  }
  const char *return_str[input_len];
  for (int i = 0; i < input_len; i++) {
    return_str[i] = &input_str[i];
  }
  return *return_str;
}

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

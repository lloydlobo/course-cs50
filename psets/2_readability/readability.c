/* [[file:../../README.org::psets/2_readability][psets/2_readability]] */
#include <ctype.h>
#include <math.h>    // add `-lm` flag while compiling.
#include <pthread.h> // add `-lpthread` flag to link lib.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

/* Constants. */

const int MALLOC = 240;
const int MALLOC_OUT = 16;
const float PER_100_WORDS = 100.0;
const char SPACE = 32;
const char PERIOD = '.';
const char EXCLAMATION = '!';
const char QUESTION = '?';

/* Forward declarations for functions, with prototypes. */

const char *prompt_text(void);
int get_count_s(char s[MALLOC]);
int count_words(char str[MALLOC], int str_count);
int count_sentences(char str[MALLOC], int str_count);
int count_letters(char str[MALLOC], int str_count);
float average_sentences(float s_len, float w_len);
float average_letters(float l_len, float w_len);
float coleman_liau_index(float letter_avg, float sentence_avg);
// TODO: sprintf format Text: + Results based on grades Before 1 --> 16+

/* Entry point for function main().

   Compile with:
   $ gcc -o readability readability.c -lm -lpthread */
int main(int argc, char *argv[]) {
  const char *string_user[MALLOC]; // const char *str[malloc];
  /* prompt user for text. */
  char s[MALLOC]; // NOTE: Prompt Text from user.
  printf("Enter text to grade with Coleman-Liau formulae:\n");
  fgets(s, sizeof(s), stdin); // printf("\nInput: %s\n", s);
  puts(s); // Write a string, followed by a newline, to stdout.
  int s_count = get_count_s(s);
  /* assign string, word, sentences, letters count. */
  int w_len = count_words(s, s_count);
  int s_len = count_sentences(s, s_count);
  int l_len = count_letters(s, s_count);
  /* calculate average letter & sentence count / 100 words. */
  float s_avg = average_sentences(s_len, w_len);
  float l_avg = average_letters(l_len, w_len);
  /* Calculate Coleman-Liau Index Grade. */
  float cli_grade = coleman_liau_index(l_avg, s_avg);
  printf("cli_grade: %f\n", cli_grade);
  return EXIT_SUCCESS;
}

/* Your program must prompt the user for a string of text using get_string.

   Your program should count the number of letters, words, and sentences in
   the text. You may assume that a letter is any lowercase character from a to z
   or any uppercase character from A to Z, any sequence of characters separated
   by spaces should count as a word, and that any occurrence of a period,
   exclamation point, or question mark indicates the end of a sentence.

   Your program should print as output "Grade X" where X is the grade level
   computed by the Coleman-Liau formula, rounded to the nearest integer.

   If the resulting index number is 16 or higher (equivalent to or greater
   than a senior undergraduate reading level), your program should output "Grade
   16+" instead of giving the exact index number. If the index number is less
   than 1, your program should output "Before Grade 1". */

/* Subtract the last escape char or NUL maybe. */
int get_count_s(char s[MALLOC]) { return strlen(s) - 1; }

int count_words(char str[MALLOC], int str_count) {
  int counter = 1; // Set atleast one word pre loop.
  for (int i = 0; i < str_count; i++) {
    if (str[i] == SPACE) {
      counter++;
    }
  }
  return counter;
}

int count_sentences(char str[MALLOC], int str_count) {
  int counter = 0; // TODO: Set atleast one sentence pre loop.
  for (int i = 0; i < str_count; i++) {
    char c = str[i];
    bool is_line_end = i == str_count - 1 && counter == 0;
    bool is_curr_sentence_end =
        c == PERIOD || c == QUESTION || c == EXCLAMATION;
    if (c == EXCLAMATION || c == QUESTION || c == PERIOD) {
      counter++; // if (is_line_end) { counter++; // for 1 sentence text. }
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
/* psets/2_readability ends here */

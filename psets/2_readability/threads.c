/* [[file:../../README.org::psets/2_readability][psets/2_readability]] */

// gcc -o readability readability.c -lm -lpthread
#include <math.h>    // add `-lm` flag while compiling.
#include <pthread.h> // add `-lpthread` flag to link lib.

#include <ctype.h>
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
// const char *get_testcases(); // Without prototype.

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
      counter++; // if (is_line_end) { counter++; // Fallback for 1 sentence
                 // text. }
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
 * engineering man - YT - Threading Basics in C.
 */
void *entry_point(void *value) {
  printf("Hello from thread two.\n");
  int *num = (int *)value;
  printf("The value of `void *value` is %d\n", *num);
  return NULL;
}

/*
 * pthreads.
 *
 */
void *pt_avg_letters(void *val) {
  printf("Hello from thread three.\n");
  float avg = *(float *)val * PER_100_WORDS; // float *num = (float *)val;
  printf("avg letters is %f\n", avg);
  float *a = &avg;
  return (void *)a;
}
void *pt_avg_sentences(void *val) {
  printf("Hello from thread four.\n");
  float avg = *(float *)val * PER_100_WORDS; // int *num = (int *)val;
  printf("avg sentences is %f\n", avg);
  float *a = &avg;
  printf("%f\n", *a);
  return (void *)a;
}

/*
 * Entry point function main().
 *
 */
int main(int argc, char *argv[]) {
  /* pthread instance 1
   * threading average STARTS here. */
  pthread_t thread; // Like a waitgroup or channel in Go?
  printf("Hello from thread one.\n");
  int num = 123;
  // For a passing a value, replace NULL.
  pthread_create(&thread, NULL, entry_point, &num); // Like a Goroutine?
  // Won't resume till all threads return.
  pthread_join(thread, NULL); // Like a wg.Wait().
  /* pthread instance 1
   * threading average ENDS here. */

  const char *string_user[MALLOC]; // const char *str[malloc];
  /* prompt user for text. */
  char s[MALLOC]; // NOTE: Prompt Text from user.
  printf("Enter text to grade with Coleman-Liau formulae:\n");
  fgets(s, sizeof(s), stdin);
  printf("\nInput: %s\n", s);
  puts(s); // Write a string, followed by a newline, to stdout.
  int s_count = get_count_s(s);

  /* assign string, word, sentences, letters count. */
  int w_len = count_words(s, s_count);
  int s_len = count_sentences(s, s_count);
  int l_len = count_letters(s, s_count);
  printf("%i, %i, %i\n", w_len, s_len, l_len);

  float avg_s = (float)s_len / w_len;
  float avg_l = (float)l_len / w_len;

  float ret_pt_s;
  float ret_pt_l;
  /* pthread instance 2
     starts here. */
  /* Starting Routine
     The name of the function that the thread starts to execute. If the
     function’s return type is void *, then its name is simply written;
     otherwise, it has to be type-cast to void . */
  // https://stackoverflow.com/questions/2251452/how-to-return-a-value-from-pthread-threads-in-c
  pthread_t pt_s;
  pthread_create(&pt_s, NULL, pt_avg_sentences, &avg_s);
  pthread_join(pt_s, (void **)&ret_pt_s);

  pthread_t pt_l;
  pthread_create(&pt_l, NULL, pt_avg_letters, &avg_l);
  pthread_join(pt_l, (void **)&ret_pt_l);
  // pthread_join(thread, NULL);               // Wait().

  printf("ret: %f, %f\n", ret_pt_s, ret_pt_l);
  printf("avg: %.2f %.2f\n", avg_s, avg_l); // FIX: 0.50, 5.00

  /* pthread instance 2
     ends here. */

  /* calculate average letter & sentence count / 100 words. */
  float s_avg = average_sentences(s_len, w_len);
  float l_avg = average_letters(l_len, w_len);
  printf("%.2f, %.2f\n", l_avg, s_avg);

  /* Calculate Coleman-Liau Index Grade. */
  float cli_grade = coleman_liau_index(l_avg, s_avg);
  printf("cli_grade: %f\n", cli_grade);

  return EXIT_SUCCESS;
}

// https://stackoverflow.com/questions/69385061/basic-usage-of-pthread-function-with-return-value
/*
void *count_lines(void *arg) {
    FILE *fh = (FILE *) arg;
    int c;
    int count = 0;
    while((c = getc(fh)) != EOF) {
        if(c == '\n') count++;
    }
    return (void *) count;
}

int main(int argc, char *argv[]) {
    pthread_t thread_id;
    if(argc != 2) {
        printf("usage: %s path_of_flie\n", argv[0]);
        return 1;
    }
    FILE *fh = fopen(argv[1], "r");
    if(!fh) {
        printf("Could not open file %s", argv[1]);
        return 1;
    }
    pthread_create(&thread_id, NULL, count_lines, fh);
    int linecount;
    pthread_join(thread_id, (void **) &linecount);
    fclose(fh);
    printf("lines: %d \n", linecount);
}

and running the program on itself it returns:

lines: 32

*/

/*
 * The program should behave per the below.
 * $ ./readability
 *
 * Text: In my younger and more vulnerable years my father gave me some advice
 * that I've been turning over in my mind ever since.
 * In my younger and more vulnerable years my father gave me some advice that
 * I've been turning over in my mind ever since.
 *
 * **** Letters
 * **** Words
 * **** Sentences
 * */

/*
 * Your program must prompt the user for a string of text using get_string.
 *
 * Your program should count the number of letters, words, and sentences in
 * the text. You may assume that a letter is any lowercase character from a to z
 * or any uppercase character from A to Z, any sequence of characters separated
 * by spaces should count as a word, and that any occurrence of a period,
 * exclamation point, or question mark indicates the end of a sentence.
 *
 * Your program should print as output "Grade X" where X is the grade level
 * computed by the Coleman-Liau formula, rounded to the nearest integer.
 *
 * If the resulting index number is 16 or higher (equivalent to or greater
 * than a senior undergraduate reading level), your program should output "Grade
 * 16+" instead of giving the exact index number. If the index number is less
 * than 1, your program should output "Before Grade 1".
 *
 * */

/*
 * One fish. Two fish. Red fish. Blue fish. (Before Grade 1)
 *
 * Would you like them here or there? I would not like them here or there. I
 * would not like them anywhere. (Grade 2)
 *
 * Congratulations! Today is your day. You're off to Great Places! You're off
 * and away! (Grade 3)
 *
 * Harry Potter was a highly unusual boy in many ways. For one thing, he hated
 * the summer holidays more than any other time of year. For another, he really
 * wanted to do his homework, but was forced to do it in secret, in the dead of
 * the night. And he also happened to be a wizard. (Grade 5)
 *
 * In my younger and more vulnerable years my father gave me some advice that
 * I've been turning over in my mind ever since. (Grade 7)
 *
 * Alice was beginning to get very tired of sitting by her sister on the bank,
 * and of having nothing to do: once or twice she had peeped into the book her
 * sister was reading, but it had no pictures or conversations in it, "and what
 * is the use of a book," thought Alice "without pictures or conversation?"
 * (Grade 8)
 *
 * When he was nearly thirteen, my brother Jem got his arm badly broken at the
 * elbow. When it healed, and Jem's fears of never being able to play football
 * were assuaged, he was seldom self-conscious about his injury. His left arm
 * was somewhat shorter than his right; when he stood or walked, the back of his
 * hand was at right angles to his body, his thumb parallel to his thigh. (Grade
 * 8)
 *
 * There are more things in Heaven and Earth, Horatio, than are dreamt of in
 * your philosophy. (Grade 9)
 *
 * It was a bright cold day in April, and the clocks were striking thirteen.
 * Winston Smith, his chin nuzzled into his breast in an effort to escape the
 * vile wind, slipped quickly through the glass doors of Victory Mansions,
 * though not quickly enough to prevent a swirl of gritty dust from entering
 * along with him. (Grade 10)
 *
 * A large class of computational problems involve the determination of
 * properties of graphs, digraphs, integers, arrays of integers, finite families
 * of finite sets, boolean formulas and elements of other countable domains.
 * (Grade 16+)
 *
 * */
/* psets/2_readability ends here */

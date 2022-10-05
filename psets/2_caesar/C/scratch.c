#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

/* Forward declaration for functions with prototypes.*/

void print_line(void);
void report_arv_len_not_enough();
void report_argv_1_not_int();
void report_argv_2_not_a_string();
void report_successful_input(char *argv[]);

/* int main()
   Caesar */
int main(int argc, char *argv[]) {
  /* Handle if no input is added. */
  if (argc < 2) {
    report_arv_len_not_enough();
    return EXIT_FAILURE; // exit.
  }

  report_successful_input(argv); // continue.

  /* argument count & vector. */

  int len_argc_bin = strlen(argv[0]);   // ./scratch.
  int len_argc_key = strlen(argv[1]);   // 13.
  int len_argc_value = strlen(argv[2]); // hello.
  int len_argc_last = strlen(argv[argc - 1]);

  /* Get input key/crypt */

  char key_temp[len_argc_key];
  for (int i = 0; i < len_argc_key; i++) {
    char *c = &argv[1][i];
    key_temp[i] = *c;
  }
  // 1. sscanf() 2. atoi() 3. Typecasting. string => int.
  int key = atoi(key_temp); // int *key = (int *)key_temp; // 13 => 13105.
  if (key < 1) {            // argv[1] is a +ve integer.
    report_argv_1_not_int();
    return EXIT_FAILURE;
  }

  /* Get input password value */

  char value_temp[len_argc_value];
  for (int i = 0; i < len_argc_value; i++) {
    char *c = &argv[2][i];
    bool is_a_to_z = *c >= 97 && *c <= 122;
    if (is_a_to_z) {
      value_temp[i] = *c;
    } else { // PERF: Doing 2 things. Collect & error handiling.
      report_argv_2_not_a_string();
      return EXIT_FAILURE;
    }
  }
  const char *value = value_temp;

  char in_str_key[len_argc_key];
  for (int i = 0; i < len_argc_key; i++) {
    in_str_key[i] = argv[1][i];
  }

  /* Prompt till the right input is received. */

  // TODO: maybe loop it?
  // while (argc == 2) ;

  /* Print from 13 to infinity. Cycles at 26 a-z. */

  /* Print results. */

  printf("argc:              %i\n", argc);         // 2.
  printf("argv[1]:           %s\n", argv[1]);      // 13.
  printf("argv[2]:           %s\n", argv[2]);      // hello.
  printf("len_argc:          %i\n", len_argc_key); // 2.
  printf("key_temp:          %s\n", key_temp);     // 2.
  printf("key:               %i\n", key);          // 2.
  printf("value_temp:        %s\n", value_temp);   // 2.
  printf("value:             %s\n", value);        // 2.
  // printf("input:             %s\n", input);    // 13.
  // printf("Secret hash key:   %2s\n", input);   // 13.

  return 0;
}

// Em dash (—)
void print_line(void) { printf("————————————————————————————\n"); }

void report_arv_len_not_enough(void) {
  printf("err: No arguments were entered.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_1_not_int(void) {
  printf("err: Entered key is not a valid positive integer.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_2_not_a_string() {
  printf("err: Entered passwords is not a valid text.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_successful_input(char *argv[]) {
  print_line();
  printf("| Secret key     :    %2s\n", argv[1]);
  printf("| Password       :    %2s\n", argv[2]);
  print_line();
}

/* int argc, char *argv[]
printf("%i %s\n", argc, argv[0]); // ./scratch
printf("%i %s\n", argc, argv[1]); // 1
printf("%i %s\n", argc, argv[2]); // null

1 ./scratch
1 (null)
1 XDG_RUNTIME_DIR=/run/user/1000 */

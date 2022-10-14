#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward funtion declarations
    with prototypes. */

int level_1_design(void);

typedef struct {
  char *name;
  char *number;
} Person;

/* Encapsulate related pieces of information.
   Image is dots (pixels) of RGB values for example.
   Similarly dataypes of music (intervals, loudness,...). */
int main(int argc, char *argv[]) {
  int return_val;
  return_val = level_1_design();
  if (return_val == 1) {
    return EXIT_FAILURE;
  } else {

    // Data types with structures.
    Person people[2];
    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";
    people[1].name = "David";
    people[1].number = "+1-999-468-2750";
    for (int i = 0; i < 2; i++) {
      if (strcmp(people[i].name, "David") == 0) {
        printf("Found %s for %s.\n", people[i].number, people[i].name);
        return_val = 0;
        return EXIT_SUCCESS;
      }
    }
    printf("Not found\n");
    return_val = EXIT_FAILURE;
  }
  return return_val;
}

/* level_1_design(
    Manual search for a phonebook. */
int level_1_design(void) {
  char *names[] = {"Carter", "David"};
  char *numbers[] = {"+1-617-495-1000", "+1-999-468-2750"};
  for (int i = 0; i < 2; i++) {
    if (strcmp(names[i], "David") == 0) {
      printf("Found %s for %s.\n", numbers[i], names[i]);
      return 0;
    }
  }
  printf("Not found\n");
  return 1;
}

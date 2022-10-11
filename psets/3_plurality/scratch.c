#include <stdbool.h>
#include <stdio.h>
#include <string.h>
// #include <cs50.h>
#define BOOL bool

// https://cs50.harvard.edu/x/2022/psets/3/

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct {
  char *name; // string name;
  int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[]) {
  printf("plurality: Week 3\n");
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: plurality [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
  }

  char prompt_voter_count[100];
  printf("Number of voters: \n");
  fgets(prompt_voter_count, sizeof(prompt_voter_count), stdin);
  int voter_count; // int voter_count = get_int("Number of voters: ");

  // Loop over all voters
  char prompt_voters[100];
  char *voters;
  for (int i = 0; i < voter_count; i++) { // string name = get_string("Vote: ");
    printf("Votes: \n");
    fgets(prompt_voters, sizeof(prompt_voters), stdin);
    char name = scanf("%s", voters);

    // Check for invalid vote
    if (!vote(&name)) {
      printf("Invalid vote.\n");
    }
  }

  // Display winner of election
  print_winner();
}

// Update vote totals given a new vote
// bool vote(string name) { // TODO return false; }
bool vote(char *name) {
  // TODO:
  return false;
}

// Print the winner (or winners) of the election
void print_winner(void) {
  // TODO:
  return;
}

// 10:45  ➜  gcc -g *.c -lm
// 10:45  ➜  gcc -g *.c -lm -o scratch

/* main()

   # Background
   Elections come in all shapes and sizes. In the UK, the Prime Minister is
   officially appointed by the monarch, who generally chooses the leader of the
   political party that wins the most seats in the House of Commons. The United
   States uses a multi-step Electoral College process where citizens vote on how
   each state should allocate Electors who then elect the President.

   Perhaps the simplest way to hold an election, though, is via a method
   commonly known as the “plurality vote” (also known as “first-past-the-post”
   or “winner take all”). In the plurality vote, every voter gets to vote for
   one candidate. At the end of the election, whichever candidate has the
   greatest number of votes is declared the winner of the election. */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BOOL bool
#define MAX 9 // Max number of candidates
#define BUFFER_SIZE 24

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
  int winner;
  int loser;
} pair;

typedef struct {
  int pref[3];
} ARRAY_2D;
ARRAY_2D cache[MAX];
typedef struct {
  int votes[MAX];
} Votes;

typedef struct {
  char *name;
  Votes votes_per_round;
  int rank;
  bool gotVoted;
  int preference;
  int id;
} CANDIDATE;
CANDIDATE C[MAX];

typedef struct {
  int input[MAX];
  int output[MAX];
} Preference;
Preference P[MAX];

typedef struct {
  int round;
  Votes Votes;
  int voter_count;
  int candidate_count;
  int votes_counter;
  int valid_votes_counter;
} Database;
Database DB;

int curr_round;
int curr_voter;
// Array of candidates
char *candidates[MAX]; // string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int main(int argc, char *argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }
  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
    C[i].name = candidates[i];
    C[i].id = i;
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = false;
    }
    printf("%s ", candidates[i]);
  }
  printf("\n");

  pair_count = 0;
  // int voter_count = get_int("Number of voters: ");
  int voter_count = 0;
  size_t mem_stdin = 100;
  char *user_prompt = malloc(mem_stdin);
  printf("Number of voters: ");
  fgets(user_prompt, sizeof(user_prompt), stdin);
  voter_count = atoi(user_prompt);
  DB.voter_count = voter_count;
  DB.candidate_count = candidate_count;

  // Query for votes
  for (int i = 0; i < voter_count; i++) {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count];
    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      char name[BUFFER_SIZE];
      printf("Rank %i: ", j + 1);
      // strchr() (string function) replaces the newline,
      // character in the string with ‘\0’ if it exists.
      // find new line and if new line is found,
      // replace with null character.
      if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Fail to read the input stream");
      } else {
        char *ptr = strchr(name, '\n');
        if (ptr) {
          *ptr = '\0';
        }
      }
      DB.votes_counter++;
      if (!vote(j, name, ranks)) {
        printf("Invalid vote.\n");
        return 3;
      }
    } // end of for j;
    record_preferences(ranks);
    curr_voter += 1;
    // Reset votes for the next voter.
    for (int i = 0; i < candidate_count; i++) {
      C[i].rank = 0;
      C[i].gotVoted = false;
      curr_round = 0;
      printf("%i", ranks[i]);
    }
    printf("\n");
  }
  printf("\n");
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      printf("%i ", P[i].output[j]);
    }
  }
  printf("\n");
  add_pairs();
  sort_pairs();
  lock_pairs();
  print_winner();
  return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[]) {
  bool isRecorded = false;
  int rank_counter;
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(name, candidates[i]) == 0) { // matches true.
      if (!C[i].gotVoted) {                 // false
        DB.valid_votes_counter++;
        curr_round++;
        C[i].rank += curr_round;
        ranks[i] = C[i].rank;
        C[i].gotVoted = true;
        isRecorded = true;
      }
    } else {
      continue;
    }
  }
  // printf("\n");
  return isRecorded;
}

/*
Ranked
1. A
2. C
3. B
Prefer
A -> A 0
A -> C 1
A -> B 2
B -> A 0
B -> C 0
B -> B 0
C -> A 0
C -> C 0
C -> B 1
// Pseudocode
Find length of candidates
Scan for each candidate
Pick A0 as pivot
Scan over [A, B, C]
Compare A to A; A to B; A to C
repeat for B0 & C0.
    if Rand of A0 is higher than B & C
        preference[i][j]++ where i is index of A0
    else if A0 scans A
        preference[i][j==i] = - where i is index of A0
*/
// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
  int length = candidate_count;
  ARRAY_2D simple_arr[candidate_count];
  // Scan A@ then B@ then C@.
  for (int i = 0; i < length; i++) {
    int curr_rank = ranks[i];
    for (int j = 0; j < length; j++) {
      int next_rank = ranks[j];
      int diff_rank = next_rank - curr_rank;
      simple_arr[i].pref[j] = 0;
      if (diff_rank > 0) { // If lesser than 0 or 1. then prefered.
        simple_arr[i].pref[j]++;
        cache[i].pref[j]++;
      } else if (diff_rank == 0) {
        simple_arr[i].pref[j] = 0;
        cache[i].pref[j] += 0;
      }
    }
  }
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      printf("%i\n", simple_arr[i].pref[j]);
    }
  }
  printf("\n");
}

// TODO: 0 3 2 3 2 0 0 2 3
// 0 3 2
// 2 0 1
// 3 1 0
// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
  int length = candidate_count;
  printf("pairs\n");

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      printf("%i", cache[i].pref[j]);
    }
  }
  int n = MAX * (MAX - 1) / 2;
  for (int i = 0; i < n; i++) {
    pairs[i].winner = C[i].id;
  }

  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  // TODO
  return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
  // TODO
  return;
}

// Print the winner of the election
void print_winner(void) {
  // TODO
  return;
}

/* https://cs50.harvard.edu/x/2022/psets/3/tideman/

# Understanding

Let’s take a look at tideman.c.
- First, notice the two-dimensional array preferences. The integer
  preferences[i][j] will represent the number of voters who prefer candidate i
  over candidate j.
- The file also defines another two-dimensional array, called locked, which will
  represent the candidate graph. locked is a boolean array, so locked[i][j]
  being true represents the existence of an edge pointing from candidate i to
  candidate j; false means there is no edge. (If curious, this representation of
  a graph is known as an “adjacency matrix”).
- Next up is a struct called pair, used to represent a pair of candidates: each
  pair includes the winner’s candidate index and the loser’s candidate index.
- The candidates themselves are stored in the array candidates, which is an
  array of strings representing the names of each of the candidates. There’s
  also an array of pairs, which will represent all of the pairs of candidates
  (for which one is preferred over the other) in the election.
- The program also has two global variables: pair_count and candidate_count,
  representing the number of pairs and number of candidates in the arrays pairs
  and candidates, respectively.
- Now onto main. Notice that after determining the number of candidates, the
  program loops through the locked graph and initially sets all of the values to
  false, which means our initial graph will have no edges in it.
- Next, the program loops over all of the voters and collects their preferences
  in an array called ranks (via a call to vote), where ranks[i] is the index of
  the candidate who is the ith preference for the voter. These ranks are passed
  into the record_preference function, whose job it is to take those ranks and
  update the global preferences variable.
- Once all of the votes are in, the pairs of candidates are added to the pairs
  array via a called to add_pairs, sorted via a call to sort_pairs, and locked
  into the graph via a call to lock_pairs. Finally, print_winner is called to
  print out the name of the election’s winner!
- Further down in the file, you’ll see that the functions vote,
  record_preference, add_pairs,sort_pairs, lock_pairs, and print_winner are left
  blank. That’s up to you! Specification

- Complete the implementation of tideman.c in such a way that it simulates a
  Tideman election.

# Complete the vote function.

- The function takes arguments rank, name, and ranks. If name is a match
  for the name of a valid candidate, then you should update the ranks array to
  indicate that the voter has the candidate as their rank preference (where 0 is
  the first preference, 1 is the second preference, etc.) Recall that ranks[i]
  here represents the user’s ith preference. The function should return true if
  the rank was successfully recorded, and false otherwise (if, for instance,
  name is not the name of one of the candidates). You may assume that no two
  candidates will have the same name. Complete the record_preferences function.
  The function is called once for each voter, and takes as argument the ranks
  array, (recall that ranks[i] is the voter’s ith preference, where ranks[0] is
  the first preference). The function should update the global preferences array
  to add the current voter’s preferences. Recall that preferences[i][j] should
  represent the number of voters who prefer candidate i over candidate j. You
  may assume that every voter will rank each of the candidates.

# Complete the add_pairs function.

- The function should add all pairs of candidates where one candidate is
  preferred to the pairs array. A pair of candidates who are tied (one is not
  preferred over the other) should not be added to the array. The function
  should update the global variable pair_count to be the number of pairs of
  candidates. (The pairs should thus all be stored between pairs[0] and
  pairs[pair_count - 1], inclusive). Complete the sort_pairs function. The
  function should sort the pairs array in decreasing order of strength of
  victory, where strength of victory is defined to be the number of voters who
  prefer the preferred candidate. If multiple pairs have the same strength of
  victory, you may assume that the order does not matter. Complete the
  lock_pairs function. The function should create the locked graph, adding all
  edges in decreasing order of victory strength so long as the edge would not
  create a cycle. Complete the print_winner function.
- The function should print out the name of the candidate who is the
  source of the graph. You may assume there will not be more than one source.
- You should not modify anything else in tideman.c other than the
  implementations of the vote, record_preferences, add_pairs, sort_pairs,
  lock_pairs, and print_winner functions (and the inclusion of additional header
  files, if you’d like). You are permitted to add additional functions to
  tideman.c, so long as you do not change the declarations of any of the
  existing functions. */

/*
 * If name is a match for the name of a valid candidate, then you should update
 * the ranks array to indicate that the voter has the candidate as their rank
 * preference (where 0 is the first preference, 1 is the second preference,
 * etc.) Recall that ranks[i] here represents the user’s ith preference. The
 * function should return true if the rank was successfully recorded, and false
 * otherwise (if, for instance, name is not the name of one of the candidates).
 * You may assume that no two candidates will have the same name.
 */
// wget https://cdn.cs50.net/2021/fall/psets/3/plurality.zip
// unzip plurality.zip
//
// https://cs50.harvard.edu/x/2022/psets/3/
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <cs50.h>
#define BOOL bool
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

void print_line(void) { printf("—————————————————————————————————\n"); }

int main(int argc, char *argv[]) {
    print_line();
    printf("Week 3 : plurality\n");
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    // Populate array of candidates
    candidate_count = argc - 1; // 5 - 1. count - binary name.
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        printf("%s: %i    ", candidates[i].name, candidates[i].votes);
    }
    printf("\n");
    print_line();
    // ..
    char prompt_voter_count[100];
    printf("Number of voters: ");
    fgets(prompt_voter_count, sizeof(prompt_voter_count), stdin);
    int n = sizeof(prompt_voter_count) / sizeof(prompt_voter_count[0]);
    int voter_count = atoi(prompt_voter_count);
    // Loop over all voters
    char usrvote[100];
    char *voters;
    printf("voter_count: %i\n", voter_count);
    for (int i = 0; i < voter_count; i++) { // string name = get_string("Vote: ");
        printf("Votes: ");
        fgets(usrvote, sizeof(usrvote), stdin);
        // Check for invalid vote if (!vote(&name)) { printf("Invalid vote.\n"); }
        // TODO: Add vote here somehow?
        // NOTE: !!! Maybe because it's not a pointer we can't compare usrvote in
        // scoped function?
        if (!vote(usrvote)) {
            printf("Invalid vote.\n");
        }
    }
    print_winner(); // Display winner of election
}

// Update vote totals given a new vote
// bool vote(string name) { // TODO return false; }
bool vote(char *name) { // printf("bool vote(...) = %s\n", name);
    int n = candidate_count;
    char *ctrim;
    const char *t_c;
    // Parse *name and remove newline.
    const char *t_n;
    int len_name = strlen(name) - 1;
    char copy[len_name];
    for (int i = 0; i < len_name; i++) {
        char c = name[i];
        copy[i] = c;
    }
    t_n = copy; // FIX: Not iterating over each candi name?
    // Compare strings.
    for (int i = 0; i < n; i++) {
        printf("n: %i\n", n);
        t_c = (candidates)[i].name;
        if (strcmp(t_c, t_n) == 0) {
            printf("Found: %s\n", t_n);
            // TODO: Add count to vote.
            // return true;
        } else {
            continue;
        }
    }
    return true;
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

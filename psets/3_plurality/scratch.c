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
    char *voters;
    // TODO: increment vote count.
    int all_valid_votes;
    printf("voter_count: %i\n", voter_count);
    for (int i = 0; i < voter_count; i++) { // string name = get_string("Vote: ");
        char usrvote[10];
        printf("Votes: ");
        fgets(usrvote, sizeof(usrvote), stdin);
        if (!vote(usrvote)) { // is vote valid?
            printf("Invalid vote.\n");
        } else {
            all_valid_votes++;
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name) {
    bool isFound = true;
    int len_name = strlen(name) - 1;
    char copy[len_name];
    const char *cache_vote;
    for (int i = 0; i < len_name; i++) {
        char c = name[i];
        copy[i] = c; // HACK: Two instance of copied values.
        cache_vote = copy;
    }
    for (int i = 0; i < candidate_count; i++) {
        const char *vote_name = cache_vote;
        const char *candidate_name = (candidates)[i].name;
        // Compare strings of same type.
        bool isAMatchVote = strcmp(candidate_name, vote_name) == 0;
        if (isAMatchVote) {
            candidates[i].votes++;
            isFound = true;
            break;
        } else {
            isFound = false;
        }
    }
    return isFound;
}

// Print the winner (or winners) of the election
void print_winner(void) {
    // TODO:
    int *ballot[candidate_count];
    int isGreater;
    int idx;
    for (int i = 0; i < candidate_count; i++) {
        ballot[i] = &candidates[i].votes;
    }
    for (int i = 0; i < candidate_count; i++) {
        printf("Winner: %i %s\n", candidates[i].votes, candidates[i].name);
        // TODO: 
        for (int j = i + 1; j < candidate_count - 1; j++) {
            if (ballot[j - 1] > ballot[j]) {
                isGreater++;
                if (idx == candidates[i].votes) {
                    printf("Winner: %i %s\n", candidates[i].votes, candidates[i].name);
                }
                idx = i;
            }
        }
    }
    // TODO: 
    printf("%i\n", idx);
    for (int i = 0; i < candidate_count; i++) {
        if (idx == candidates[i].votes) {
            printf("Winner: %i %s\n", candidates[i].votes, candidates[i].name);
        }
    }
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

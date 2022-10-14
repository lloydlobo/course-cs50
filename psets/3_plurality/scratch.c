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

// TODO:
// Print the winner (or winners) of the election
void print_winner(void) {
    typedef struct {
        int Rank;
        candidate Candidate;
    } Ballot;
    int *ballot[candidate_count];
    int maxi, maxj;
    int idx;
    // A array of capacity n^2 which collects the id.
    // Then count the max instance of that number in the array?
    int cache[candidate_count * candidate_count];
    for (int i = 0; i < candidate_count; i++) {
        ballot[i] = &candidates[i].votes;
    }
    // [2,3,1] --> how will you sort this?
    typedef struct {
        int rI;
        int rNumI;
        int rJ;
        int rNumJ;
    } RankTest;
    int test[] = {2, 3, 1, 9, 8, 7, 9, 6, 5, 4};
    int n = sizeof(test) / sizeof(test[0]);
    RankTest r[n];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (test[i] > test[j]) {
                maxi = test[i];
                r[i].rI = i;
                r[i].rJ = j;
                r[i].rNumI = test[i];
                r[i].rNumJ = test[j];
                // break;
                // printf("test greater: %i at index: %i\n", test[i], i);
            } else if (test[j] > test[i]) {
                maxj = test[j];
                // break;
            }
            printf(" %i ", (r)[i].rI);
            printf("ni:> %i <", (r)[i].rNumI);
            printf(" %i ", (r)[i].rJ);
            printf("nj:> %i <\n", (r)[i].rNumJ);
        } // printf("maxi: %i | maxj: %i\n", maxi, maxj);
    }   // HACK: Add last element too.
    int len_ranks = sizeof(r) / sizeof(r[0]);
    typedef struct {
        int Index;
        int Number;
    } RankWinner;
    RankWinner rw[len_ranks - 1];
    for (int i = 0; i < len_ranks - 1; i++) {
        printf(" %i ", r[i].rNumI);
        // TODO: Collect ranks.
        for (int j = i + 1; j < len_ranks; j++) {
            if (r[i].rNumI > r[j].rNumJ) {
                rw[i].Index = i;
                rw[i].Number = r[i].rNumI;
                break;
            } else if (r[i].rNumI == r[j].rNumI) {
                rw[i].Index = i;
                rw[i].Number = r[i].rNumI;
            }
        }
    }

    printf("rw \n");
    for (int i = 0; i < len_ranks; i++) {
        printf("!! %i ", rw[i].Number);
    }
    printf("rw  end\n");
    printf("\n");
    // TODO: First find biggest number.
    RankWinner temp[len_ranks - 1];
    for (int prev = 0; prev < len_ranks - 1; prev++) {
        for (int curr = prev + 1; curr < len_ranks; curr++) {
            temp[prev].Number = rw[prev].Number;
            temp[prev].Index = rw[prev].Index;
            if (rw[prev].Number > rw[curr].Number ||
                rw[prev].Number == rw[curr].Number) {
                rw[prev].Number = rw[curr].Number;
                rw[prev].Index = rw[curr].Index;
                rw[curr].Number = temp[prev].Number;
                rw[curr].Index = temp[prev].Index;
                // break;
            } else if (rw[prev].Number <= rw[curr].Number) {
                continue;
            }
        }
        printf("~ %i %i ~", rw[prev].Index, rw[prev].Number);
    }
    printf("\n");
    printf("rw \n");
    // TODO: Then find it frequency.
    int draw_count = 0;
    for (int i = len_ranks - 1; i >= 0; i--) {
        printf("id %i ", rw[i].Index);
        printf("!! %i ", rw[i].Number);
        if (rw[len_ranks - 1].Number == rw[i].Number) {
            draw_count++;
        }
    }
    printf("draw count: %i\n", draw_count);
    printf("rw  end\n");
    // Declare winner.
    for (int i = 0; i < draw_count; i++) {
        RankWinner w = rw[len_ranks - 1 - i];
        printf("Winner: %i, Rank_Area: %i\n", w.Number, w.Index);
    }
    // Last, return the indexes of the gretest number.
    printf("\n");
    candidate C[candidate_count];
    // TODO:
    for (int i = 0; i < candidate_count; i++) {
        C[i] = candidates[i];
        printf("Winner: %i %s\n", candidates[i].votes, candidates[i].name);
        for (int j = i + 1; j < candidate_count - 1; j++) {
            if (ballot[j - 1] > ballot[j]) {
                maxi++;
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

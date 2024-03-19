#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool cycled[MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_cycle(int from, int to, int first_from, int first_to);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int winner = ranks[i];

        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && i < j)
            {
                int loser = ranks[j];
                preferences[winner][loser]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && i < j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int swap;
    do
    {
        swap = 0;
        for (int n = 0; n < pair_count - 1; n++)
        {
            int first_val = preferences[pairs[n].winner][pairs[n].loser];
            int sec_val = preferences[pairs[n + 1].winner][pairs[n + 1].loser];
            if (first_val < sec_val)
            {
                int temp_win = pairs[n].winner;
                int temp_lose = pairs[n].loser;
                pairs[n].winner = pairs[n + 1].winner;
                pairs[n].loser = pairs[n + 1].loser;
                pairs[n + 1].winner = temp_win;
                pairs[n + 1].loser = temp_lose;
                swap++;
            }
        }
    } while (swap > 0);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (check_cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // for (int i = 0; i < pair_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         if (j != pairs[i].winner && j != pairs[i].loser)
    //         {
    //             if (locked[j][pairs[i].winner] == true)
    //             {
    //                 break;
    //             }
    //             else if (j == candidate_count - 1)
    //             {
    //                 printf("%s\n", candidates[pairs[i].winner]);
    //                 return;
    //             }
    //         }
    //     }
    // }

    // for (int i = 0; i < pair_count; i++)
    // {
    //     int winner = pairs[i].winner;
    //     for (int j = 0; j < pair_count; j++)
    //     {
    //         int test_winner = pairs[j].winner;
    //         if (winner != test_winner)
    //         {
    //             if (locked[test_winner][winner] == true)
    //             {
    //                 break;
    //             }
    //         }
    //         if (j == pair_count - 1)
    //         {
    //             printf("%s\n", candidates[winner]);
    //         }
    //     }
    // }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (locked[j][i] == true)
                {
                    break;
                }
            }
            if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }

    return;
}

bool check_cycle(int from, int to, int first_from, int first_to)
{
    int i = to;

    for (int x = 0; x < candidate_count; x++)
    {
        if (x != from && x != to)
        {
            if (locked[i][x] == true)
            {
                if (i == first_from && x == first_to)
                {
                    return true;
                }
                else
                {
                    if (check_cycle(i, x, first_from, first_to) == true)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;

    // do
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         if (cycled[j] == false)
    //         {
    //             if (locked[i][j] == true)
    //             {
    //                 if (j == from)
    //                 {
    //                     return true;
    //                 }
    //                 else
    //                 {
    //                     cycled[i] = true;
    //                     i = j;
    //                     break;
    //                 }
    //             }
    //         }
    //         if (j == candidate_count - 1)
    //         {
    //             return false;
    //         }
    //     }
    // } while (true);

    // return false;
}
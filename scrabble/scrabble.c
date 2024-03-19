#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Compare the two scores
    if (score1 > score2)
    {
        // Player 1 wins if it has greater score than Player 2
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        // Player 2 wins if it has greater score than Player 1
        printf("Player 2 wins!\n");
    }
    else
    {
        // It's a tie if two players have the same score
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    char letter;

    // Loop through the entire string
    for (int i = 0; word[i]; i++)
    {
        // Force lowercase the letter of each word...
        // ...then assign it to a varible
        letter = tolower(word[i]);
        // Compare the letter to every letter in the alphabet...
        // ...then add score from the points array accordingly
        if (letter == 'a')
        {
            score += POINTS[0];
        }
        else if (letter == 'b')
        {
            score += POINTS[1];
        }
        else if (letter == 'c')
        {
            score += POINTS[2];
        }
        else if (letter == 'd')
        {
            score += POINTS[3];
        }
        else if (letter == 'e')
        {
            score += POINTS[4];
        }
        else if (letter == 'f')
        {
            score += POINTS[5];
        }
        else if (letter == 'g')
        {
            score += POINTS[6];
        }
        else if (letter == 'h')
        {
            score += POINTS[7];
        }
        else if (letter == 'i')
        {
            score += POINTS[8];
        }
        else if (letter == 'j')
        {
            score += POINTS[9];
        }
        else if (letter == 'k')
        {
            score += POINTS[10];
        }
        else if (letter == 'l')
        {
            score += POINTS[11];
        }
        else if (letter == 'm')
        {
            score += POINTS[12];
        }
        else if (letter == 'n')
        {
            score += POINTS[13];
        }
        else if (letter == 'o')
        {
            score += POINTS[14];
        }
        else if (letter == 'p')
        {
            score += POINTS[15];
        }
        else if (letter == 'q')
        {
            score += POINTS[16];
        }
        else if (letter == 'r')
        {
            score += POINTS[17];
        }
        else if (letter == 's')
        {
            score += POINTS[18];
        }
        else if (letter == 't')
        {
            score += POINTS[19];
        }
        else if (letter == 'u')
        {
            score += POINTS[20];
        }
        else if (letter == 'v')
        {
            score += POINTS[21];
        }
        else if (letter == 'w')
        {
            score += POINTS[22];
        }
        else if (letter == 'x')
        {
            score += POINTS[23];
        }
        else if (letter == 'y')
        {
            score += POINTS[24];
        }
        else if (letter == 'z')
        {
            score += POINTS[25];
        }
        // Add nothing to the score if the character is not a letter
        else
        {
            score += 0;
        }
    }

    // Function returns the final score
    return score;
}

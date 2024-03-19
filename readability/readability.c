#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function prototypes for counting letters, words, and sentences
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user to input text
    string inputText = get_string("Text: ");

    // Call functions to count letters, words, and sentences
    int letters = count_letters(inputText);
    int words = count_words(inputText);
    int sentences = count_sentences(inputText);

    // Compute the average letters and sentences per 100 words
    float averageLetters = letters / (float) words * 100;
    float averageSentences = sentences / (float) words * 100;
    // Use Coleman-Liau index formula
    float readingIndex = 0.0588 * averageLetters - 0.296 * averageSentences - 15.8;
    // Round the index to the nearest integer
    int finalIndex = round(readingIndex);

    // For manual debugging
    // printf("%i letters\n", letters);
    // printf("%i words\n", words);
    // printf("%i sentences\n", sentences);
    // printf("%f letters per 100 words\n", averageLetters);
    // printf("%f sentences per 100 words\n", averageSentences);
    // printf("%f floating index\n", readingIndex);
    // printf("%i rounded index\n", finalIndex);

    // Print the reading level according to the index
    if (finalIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (finalIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", finalIndex);
    }
}

int count_letters(string text)
{
    int numberOfLetters = 0;
    for (int i = 0; text[i]; i++)
    {
        if (isalpha(text[i]))
        {
            numberOfLetters++;
        }
    }

    return numberOfLetters;
}
int count_words(string text)
{
    int numberOfWords = 1;
    for (int i = 0; text[i]; i++)
    {
        if (isspace(text[i]))
        {
            numberOfWords++;
        }
    }

    return numberOfWords;
}
int count_sentences(string text)
{
    int numberOfSentences = 0;
    for (int i = 0; text[i]; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            numberOfSentences++;
        }
    }

    return numberOfSentences;
}
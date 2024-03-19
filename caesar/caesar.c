#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Function prototype for checking if the comand-line argument are digits
bool only_digits(string s);
// Function prototype for adding Caesar's encryption to the letters
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Check if the command-line arguments have only one number as key
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check if the command-line argument received as string contains only digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Convert the string command-line arguement into an int
    int key = atoi(argv[1]);

    // Prompt user for the plaintext
    string text = get_string("plaintext:  ");

    printf("ciphertext: ");
    // Cycle through every letter in the plaintext then perfom the encryption according to the key
    for (int i = 0; text[i]; i++)
    {
        printf("%c", rotate(text[i], key));
    }
    printf("\n");

    return 0;
}

bool only_digits(string s)
{
    for (int i = 0; s[i]; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
char rotate(char c, int n)
{
    if (!isalpha(c))
    {
        return c;
    }

    n %= 26;
    for (int i = 0; i < n; i++)
    {
        c++;
        if (!isalpha(c))
        {
            c -= 26;
        }
    }
    return c;
}
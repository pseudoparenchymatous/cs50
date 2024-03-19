#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Will be used to test if KEY contains every letter in the alphabet exactly once
int LETTEROCCUR[26];

bool is_key_alpha(string s);
bool valid_key(string s);
char subs(char c, string key);

int main(int argc, string argv[])
{
    // Throw error if no KEY or more than one KEY is provided
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Throw error if KEY doesn't contain exactly 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    // Throw error if KEY contains non-alphabet characters
    if (!is_key_alpha(argv[1]))
    {
        printf("Key must contain alphabet characters only\n");
        return 1;
    }
    // Throw error if KEY doesn't contain every letter in the alphabet exactly once
    if (!valid_key(argv[1]))
    {
        printf("Key must contain every letter in the alphabet exactly once\n");
        return 1;
    }

    // Prompt for the plaintext
    string plain = get_string("plaintext:  ");
    // Prepare to input the encrypted text
    printf("ciphertext: ");

    // Loop through every character in the string and encrypt
    for (int i = 0; plain[i]; i++)
    {
        printf("%c", subs(plain[i], argv[1]));
    }
    printf("\n");
}

bool valid_key(string s)
{
    int l = 0;
    for (int i = 0; s[i]; i++)
    {
        l = toupper(s[i]) - 65;
        // Increment LETTEROCCUR everytime such letter is encountered
        LETTEROCCUR[l]++;
        // If such letter occured more than once, KEY is not valid
        if (LETTEROCCUR[l] > 1)
        {
            return false;
        }
    }
    return true;
}
bool is_key_alpha(string s)
{
    for (int i = 0; s[i]; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}
char subs(char c, string key)
{
    int l = 0;
    // If character is not an alpha, no encryption, return as is
    if (!isalpha(c))
    {
        return c;
    }
    // Encrypt/substitute characters according to their upper/lower case-ness
    if (isupper(c))
    {
        l = c - 65;
        return toupper(key[l]);
    }
    l = c - 97;
    return tolower(key[l]);
}
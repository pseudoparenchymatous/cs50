// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *search_node = table[index];
    while (search_node != NULL)
    {
        if (strcasecmp(search_node->word, word) == 0)
        {
            return true;
        }
        search_node = search_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += toupper(word[i]);
    }
    return sum % N;
}

unsigned int number_ofWords = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    char current_word[LENGTH];
    while (fscanf(dictionary_file, "%s", current_word) != EOF)
    {
        node *current_node = malloc(sizeof(node));
        if (current_node == NULL)
        {
            return false;
        }

        strcpy(current_node->word, current_word);
        current_node->next = NULL;

        unsigned int index = hash(current_word);
        if (table[index] == NULL)
        {
            table[index] = current_node;
        }
        else
        {
            // Else called
            current_node->next = table[index];
            table[index] = current_node;
        }
        number_ofWords++;
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return number_ofWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *current_node = table[i];
            node *free_me = NULL;
            while (current_node != NULL)
            {
                free_me = current_node;
                current_node = current_node->next;
                free(free_me);
            }
        }
    }
    return true;
}

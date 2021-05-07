// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;
unsigned int dictionary_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the index of the word
    unsigned int index = hash(word);

    // Make a new node
    node *n = table[index];

    while (n != NULL)
    {
        // Check for same word
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        // Go to the next node
        n = n->next;
    }

    // If not found - return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
//     // Note: hash function used from:
//     // http://www.cse.yorku.ca/~oz/hash.html

    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // New word that will be read every line
    char new_word[LENGTH + 1];
    while (fscanf(file, "%s", new_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, new_word);
        unsigned int index = hash(new_word);

        // Point to the next node
        n->next = table[index];
        table[index] = n;

        // Increase the words
        dictionary_size += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dictionary_size > 0)
    {
        return dictionary_size;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node *n = table[i];

        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }
    return false;
}


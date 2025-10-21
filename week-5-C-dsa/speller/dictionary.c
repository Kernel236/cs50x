// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table (must match modulus in hash())
const unsigned int N = 62;
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary (case-insensitive), else false
bool check(const char *word)
{
    int index = hash(word);
    node *ptr;
    for (ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word);
    unsigned int hash_value = 0;
    
    for (int i = 0; i < length; i++)
    {
        char c = toupper(word[i]);
        if (c >= 'A' && c <= 'Z')
        {
            hash_value = (hash_value * 73 + (c - 'A')) % N;
        }
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
/**
 * Loads dictionary into memory.
 *
 * @param dictionary The path to the dictionary file to load.
 * @return true if the dictionary was loaded successfully, false otherwise.
 */
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    while (fscanf(source, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            perror("malloc failed");
            fclose(source);
            return false;
        }
        strcpy(n->word, word);
        word_count++;
        n->next = NULL;

        unsigned int index = hash(n->word);
        n->next = table[index];
        table[index] = n;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{   
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}

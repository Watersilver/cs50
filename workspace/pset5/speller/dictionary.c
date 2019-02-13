// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return search_trie(dictionTrie, word);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dictionTrie = new_trie();
    wordsInDict = 0;
    // Open dictionary
    FILE *dictionFile = fopen(dictionary, "r");
    if (dictionFile == NULL)
    {
        puts("Failed to open dictionary");
        delete_trie(dictionTrie);
        return false;
    }

    // Temporary dictionary word storage
    char word[45];

    // Loop until end of file
    while (fscanf(dictionFile, "%s", word) != EOF)
    {
        if (!insert_to_trie(dictionTrie, word))
        {
            puts("Failed to load dictionary to trie");
            fclose(dictionFile);
            delete_trie(dictionTrie);
            return false;
        }
        wordsInDict++;
    }

    // Close dictionary
    fclose(dictionFile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsInDict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return delete_trie(dictionTrie);;
}

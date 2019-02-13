#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

// Function that returns an initialized new trie
TrieNode *new_trie(void)
{
    TrieNode *trie = malloc(sizeof * trie);
    if (trie == NULL)
    {
        return NULL;
    }
    trie->wordExists = false;
    for (int i = 0; i < BRANCHES_NUM; i++)
    {
        trie->branches[i] = NULL;
    }
    return trie;
}

// Inserts value to trie, making branches as necessary
bool insert_to_trie(TrieNode *root, const char *key)
{
    // Convert key string to trie index
    int keyLength = strlen(key);
    int *keyArray = convert_string_key_to_index(key, keyLength);
    if (!keyLength)
    {
        free(keyArray);
        return false;
    }

    // Inserting starts here
    // Declare traversal pointer
    TrieNode *trav = root;
    // Iterate over key
    for (int i = 0; i < keyLength; i++)
    {
        // If trav->branches[keyArray[i]] points to NULL, grow the trie and connect the current node with the new
        if (trav->branches[keyArray[i]] == NULL)
        {
            trav->branches[keyArray[i]] = new_trie();
            if (trav->branches[keyArray[i]] == NULL)
            {
                return false;
            }
        }
        // move to next node
        trav = trav->branches[keyArray[i]];
    }
    // Reached destination, insert value
    trav->wordExists = true;

    free(keyArray);
    return true;
}

// Returns if value exists in fed trie
bool search_trie(TrieNode *root, const char *key)
{
    // Convert key string to trie index
    int keyLength = strlen(key);
    int *keyArray = convert_string_key_to_index(key, keyLength);
    if (!keyLength)
    {
        free(keyArray);
        return false;
    }

    // Declare traversal pointer
    TrieNode *trav = root;
    // Iterate over key
    for (int i = 0; i < keyLength; i++)
    {
        // If trav->branches[(keyArray[i]] points to NULL, grow the trie and connect the current node with the new
        if (trav->branches[keyArray[i]] == NULL)
        {
            free(keyArray);
            return false;
        }
        // move to next node
        trav = trav->branches[keyArray[i]];
    }

    free(keyArray);
    return trav->wordExists;
}

// Frees trie from memory
bool delete_trie(TrieNode *root)
{
    // Iterate over all branches of node
    for (int i = 0; i < BRANCHES_NUM; i++)
    {
        // Delete branches that exist
        if (root->branches[i] != NULL)
        {
            delete_trie(root->branches[i]);
        }
    }
    // Free node
    free(root);
    return true;
}


// Returns converted key
int *convert_string_key_to_index(const char *key, int arrayLength)
{
    int *keyArray = malloc(sizeof * keyArray * arrayLength);
    if (keyArray == NULL)
    {
        return 0;
    }

    // Convert key string to trie index
    for (int i = 0; key[i] != '\0'; i++)
    {
        // Only convert if the chars are ' or alphabetical
        if (key[i] == '\'')
        {
            keyArray[i] = BRANCHES_NUM - 1;
        }
        else if (isalpha(key[i]))
        {
            keyArray[i] = tolower(key[i]) - 'a';
        }
        else
        {
            return NULL;
        }
    }
    return keyArray;
}

#include <stdbool.h>

#define BRANCHES_NUM 27

typedef struct TrieNode
{
    bool wordExists;
    // The key is the english alphabet plus '
    struct TrieNode *branches[BRANCHES_NUM];
} TrieNode;

TrieNode *new_trie(void);

bool insert_to_trie(TrieNode *root, const char *key);

bool search_trie(TrieNode *root, const char *key);

bool delete_trie(TrieNode *root);


TrieNode *dictionTrie;
unsigned int wordsInDict;

int *convert_string_key_to_index(const char *key, int arrayLength);

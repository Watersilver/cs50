#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

int main(void)
{
    TrieNode *testTrie = new_trie();

    char *key = "erty";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "erte";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "erta";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "mama";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "yo";
    insert_to_trie(testTrie, key);
    key = "YO";
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "a";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "'''''";
    insert_to_trie(testTrie, key);
    printf("%i\n", (int) search_trie(testTrie, key));
    key = "''''a";
    printf("%i\n", (int) search_trie(testTrie, key));
}

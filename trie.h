#include <stdlib.h>
#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
    void *data;
    struct TrieNode *parent;
    struct TrieNode *children[27];
} TrieNode;

typedef struct Trie {
    TrieNode *root;
    size_t dataSize;
    int nodeCount;
} *Trie;

Trie createTrie();
void insert(Trie trie, void *data);
void BFSPrint(Trie trie);
void destoryTrie(Trie trie);
#endif
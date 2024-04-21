#include <stdbool.h>
#include <stdlib.h>
#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
    void *data;
    struct TrieNode *parent;
    struct TrieNode *children[27];
    bool isRoot;
} TrieNode;

typedef struct Trie {
    TrieNode *root;
    size_t dataSize;
    int nodeCount;
} *Trie;

Trie createTrie();
void insert(Trie trie, void *data);
void BFSPrint(Trie trie);
void getNumberOfLeafs(TrieNode *root, int *numberOfLeafs);
void getNumberOfKSuffixes(TrieNode *root, int k, int *numberOfLetters, int *numberOfSuffixes);
void getMaxNumberOfChildren(TrieNode *root, int *maxChildren);
void destoryTrie(Trie trie);

#endif
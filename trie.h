#include <stdbool.h>
#include <stdlib.h>
#define CHILDREN_NUMBER 27
#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
    void *data;
    struct TrieNode *parent;
    struct TrieNode *children[CHILDREN_NUMBER];
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
void findSuffix(TrieNode *node, char *word, int *i, FILE *file);
void destoryTrie(Trie trie);

#endif
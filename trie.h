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

Trie createTrie(size_t dataSize);
void insertByLetter(Trie trie, void *data);
void BFSPrint(Trie trie, FILE *file);
void getNumberOfLeafs(TrieNode *root, int *numberOfLeafs, FILE *file);
void getNumberOfKSuffixes(TrieNode *root, int k, int *numberOfLetters,
                          int *numberOfSuffixes, FILE *file);
void getMaxNumberOfChildren(TrieNode *root, int *maxChildren, FILE *file);
void searchSuffix(TrieNode *root, char *word, int *i, FILE *file);
void destoryTrie(Trie trie);
void makeCompactTrie(Trie trie, char *data);
#endif
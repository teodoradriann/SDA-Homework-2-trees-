#include <stdlib.h>
#ifndef TRIE_H
#define TRIE_H

typedef struct Node {
    void *data;
    struct Node *parent;
    struct Node *children[27];
} Node;

typedef struct Trie {
    Node *root;
    size_t dataSize;
    int nodeCount;
} *Trie;

void insert(Trie trie, void *data);
#endif
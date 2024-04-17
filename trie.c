#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

Trie createTrie() {
    Trie trie = malloc(sizeof(Trie));
    trie->dataSize = sizeof(char *);
    trie->root = NULL;
    trie->nodeCount = 0;
}

Node *createNode(Trie trie, void *data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(trie->dataSize);
    if (data == NULL) {
        char dollar = '$';
        memcpy(newNode->data, &dollar, trie->dataSize);
    }
    else memcpy(newNode->data, data, trie->dataSize);
    // setez tot vectorul de copii la 0 pentru nodul nou alocat
    memset(newNode->children, 0, sizeof(newNode->children));
    return newNode;
}

void insert(Trie trie, void *data) {
    char *word = (char *)data;
    int wordLength = strlen(word);
    // daca trie-ul e gol, voi adauga direct $ care va ramane
    // acolo pe toata durata de viata a trie-ului deoarece
    // fiecare cuvant are un $ la sfarsit
    if (trie->root->children[0] == NULL) {
        trie->root->children[0] = createNode(trie, NULL);
        trie->nodeCount++;
    }
    else {
        for (int start = wordLength - 1; start >= 0; start--) {
            // plec din root
            Node *node = trie->root;
            for (int i = start; i < wordLength; i++) {
                // calculez index-ul din vectorul children
                int index = word[i] - 'a' + 1;
                if (node->children[index] == NULL) {
                    node->children[index] = createNode(trie, word[i]);
                    trie->nodeCount++;
                }
                node = node->children[index];
            }
            if (node->children[0] == NULL) {
                node->children[0] = createNode(trie, NULL);
                trie->nodeCount++;
            }
        }
    }
}

// voi utiliza o parcurgere BFS pentru a printa Trie-ul
void BFSPrint(Trie trie) {
    
}
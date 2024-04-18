#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "utils.h"

TrieNode *createTrieNode(Trie trie, void *data) {
    TrieNode *newNode = malloc(sizeof(TrieNode));
    checkMalloc(newNode);
    if (data == NULL) {
        newNode->data = NULL;
    }
    else {
        newNode->data = malloc(trie->dataSize);
        checkMalloc(newNode->data);
        memcpy(newNode->data, data, trie->dataSize);
    }
    newNode->parent = NULL;
    newNode->isRoot = false;
    // setez tot vectorul de copii la 0 pentru nodul nou aloca;
    memset(newNode->children, 0, 27 * sizeof(TrieNode *));
    return newNode;
}

Trie createTrie() {
    Trie trie = malloc(sizeof(struct Trie));
    checkMalloc(trie);
    trie->dataSize = sizeof(char *);
    trie->root = createTrieNode(trie, NULL);
    trie->nodeCount = 0;
    trie->root->isRoot = true;
    return trie;
}

void insert(Trie trie, void *data) {
    char *word = (char *)data;
    int wordLength = strlen(word);
    char *endOfWord = malloc(sizeof(char *));
    checkMalloc(endOfWord);
    *endOfWord = '$';
    // daca trie-ul e gol, voi adauga direct $ care va ramane
    // acolo pe toata durata de viata a trie-ului deoarece
    // fiecare cuvant are un $ la sfarsit
    if (trie->root->children[0] == NULL) {
        trie->root->children[0] = createTrieNode(trie, endOfWord);
        trie->nodeCount++;
    }
    for (int i = wordLength; i >= 0; i--) {
        // plec din root
        TrieNode *node = trie->root;
        for (int j = i; j < wordLength; j++) {
            // calculez index-ul din vectorul children
            int index = word[j] - 'a' + 1;
            if (node->children[index] == NULL) {
                char *data = malloc(sizeof(char *));
                checkMalloc(data);
                *data = word[i];
                node->children[index] = createTrieNode(trie, data);
                node->children[index]->parent = node;
                trie->nodeCount++;
                free(data);
            }
            node = node->children[index];
        }
        if (node->children[0] == NULL) {
            node->children[0] = createTrieNode(trie, endOfWord);
            trie->nodeCount++;
        }
    }
    free(endOfWord);
}

// voi utiliza o parcurgere BFS pentru a printa Trie-ul
void BFSPrint(Trie trie) {
    // pointer la un vector de structuri TrieNode
    TrieNode** queue = malloc(trie->nodeCount * sizeof(TrieNode*));
    checkMalloc(queue);
    memset(queue, 0, trie->nodeCount * sizeof(TrieNode *));
    int front = 0;
    int rear = 0;

    for (int i = 0; i < 27; i++) {
        if (trie->root->children[i] != NULL) {
            queue[rear++] = trie->root->children[i];
        }
    }
    //marchez sfarsitul randului cu NULL
    queue[rear++] = NULL;

    while (front != rear) {
        TrieNode *node = queue[front++];
        if (node == NULL) {
            printf("\n");
            if (front != rear) {
                if (rear == trie->nodeCount) {
                    queue = realloc(queue, trie->nodeCount * 2 * sizeof(TrieNode*));
                    checkMalloc(queue);
                }
                queue[rear++] = NULL;
            }
        } else {
            printf("%c ", *(char *)node->data);
            for (int i = 0; i < 27; i++) {
                if (node->children[i] != NULL) {
                    if (rear == trie->nodeCount) {
                        queue = realloc(queue, trie->nodeCount * 2 * sizeof(TrieNode*));
                        checkMalloc(queue);
                    }
                    queue[rear++] = node->children[i];
                }
            }
        }
        
    }
    free(queue);
}

void countLeafs(TrieNode *node, int *numberOfLeafs) {
    if (node == NULL)
        return;
    for (int i = 0; i < 27; i++) {
        if (node->children[i] != NULL) {
            if (node->children[i]->data != NULL) {
                if (*(char *)node->children[i]->data == '$')
                    (*numberOfLeafs)++;
            }
            countLeafs(node->children[i], numberOfLeafs);
        }
    }
}

void getNumberOfLeafs(TrieNode *root, int *numberOfLeafs) {
    if (root->isRoot)
        countLeafs(root, numberOfLeafs);
    else {
        printf("You need to give me the root of the tree.");
        return;
    }
}

void countSuffixes(TrieNode *node, int k, int *numberOfLetters, int *numberOfSuffixes) {
    if (node == NULL)
        return;

    if (!node->isRoot) {
        if (*(char *)node->data == '$') {
            if (k == *numberOfLetters)
                (*numberOfSuffixes)++;
        }
    }
    for (int i = 0; i < 27; i++) {
        if (node->children[i] != NULL) {
            if (node->children[i]->data != NULL) {
                if (*(char *)node->children[i]->data != '$')
                    (*numberOfLetters)++;
            }
            countSuffixes(node->children[i], k, numberOfLetters, numberOfSuffixes);
            // cand urc inapoi in arbore scad numarul de litere pe care 
            // le-am adunat pana in prezent
            if (node->children[i]->data != NULL) {
                if (*(char *)node->children[i]->data != '$')
                    (*numberOfLetters)--;
            }
        }
    }
}

void getNumberOfKSuffixes(TrieNode *root, int k, int *numberOfLetters, int *numberOfSuffixes) {
    if (root->isRoot) {
        *numberOfLetters = 0;
        *numberOfSuffixes = 0;
        countSuffixes(root, k, numberOfLetters, numberOfSuffixes);
    }
    else {
        printf("You need to give me the root of the tree.");
        return;
    }
}

void destoryTrie(Trie trie) {
    TrieNode** queue = malloc(trie->nodeCount * sizeof(TrieNode*));
    checkMalloc(queue);
    memset(queue, 0, trie->nodeCount * sizeof(TrieNode*));
    int front = 0;
    int rear = 0;

    for (int i = 0; i < 27; i++) {
        if (trie->root->children[i] != NULL) {
            queue[rear++] = trie->root->children[i];
        }
    }

    while (front != rear) {
        TrieNode *node = queue[front++];
        if (node->data != NULL) {
            free(node->data);
        }
        for (int i = 0; i < 27; i++) {
            if (node->children[i] != NULL) {
                queue[rear++] = node->children[i];
            }
        }
        free(node);
    }

    free(queue);
    free(trie->root);
    free(trie);
}
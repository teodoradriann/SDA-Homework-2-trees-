#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

TrieNode *createTrieNode(Trie trie, void *data) {
    TrieNode *newNode = malloc(sizeof(TrieNode));
    if (newNode == NULL) {
        printf("error in allocating mem for a new node");
        exit(0);
    }
    if (data == NULL) {
        newNode->data = NULL;
    }
    else {
        newNode->data = malloc(trie->dataSize);
        if (newNode->data == NULL) {
            free(newNode);
            exit(0);
        }
        memcpy(newNode->data, data, trie->dataSize);
    }
    newNode->parent = NULL;
    // setez tot vectorul de copii la 0 pentru nodul nou aloca;
    memset(newNode->children, 0, 27 * sizeof(TrieNode *));
    return newNode;
}

Trie createTrie() {
    Trie trie = malloc(sizeof(struct Trie));
    if (trie == NULL) {
        printf("error in allocating mem for a new trie");
        exit(0);
    }
    trie->dataSize = sizeof(char *);
    trie->root = createTrieNode(trie, NULL);
    trie->nodeCount = 0;
    return trie;
}

void insert(Trie trie, void *data) {
    char *word = (char *)data;
    int wordLength = strlen(word);
    char *endOfWord = malloc(sizeof(char *));
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
                    if (queue == NULL) {
                        free(queue);
                        exit(0);
                    }
                }
                queue[rear++] = NULL;
            }
        } else {
            printf("%c ", *(char *)node->data);
            for (int i = 0; i < 27; i++) {
                if (node->children[i] != NULL) {
                    if (rear == trie->nodeCount) {
                        queue = realloc(queue, trie->nodeCount * 2 * sizeof(TrieNode*));
                        if (queue == NULL) {
                            free(queue);
                            exit(0);
                        }
                    }
                    queue[rear++] = node->children[i];
                }
            }
        }
        
    }
    free(queue);
}

void destoryTrie(Trie trie) {
    TrieNode** queue = malloc(trie->nodeCount * sizeof(TrieNode*));
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
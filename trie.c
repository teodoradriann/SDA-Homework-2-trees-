#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "utils.h"

TrieNode *createTrieNode(Trie trie, void *data) {
    TrieNode *newNode = malloc(sizeof(TrieNode));
    checkMalloc(newNode);
    // pasez NULL functiei doar pentru radacina
    if (data == NULL) {
        newNode->data = NULL;
    }
    else {
        // daca avem o trie in care un nod e un singur caracter sau un string
        // atunci vom face aceeasi idee de alocare,lungimea stringului + 1 (\0)
        // pentru alte cazuri de trie alte if-uri cu alocarile de rigoare
        if (trie->dataSize == sizeof(char) || trie->dataSize == sizeof(char *)) {
            newNode->data = malloc(strlen((char *)data) + 1);
            checkMalloc(newNode->data);
            memcpy(newNode->data, data, strlen((char *)data) + 1);
        }
    }
    newNode->parent = NULL;
    newNode->isRoot = false;
    // setez tot vectorul de copii la 0 pentru nodul nou aloca;
    memset(newNode->children, 0, CHILDREN_NUMBER * sizeof(TrieNode *));
    return newNode;
}

Trie createTrie(size_t dataSize) {
    Trie trie = malloc(sizeof(struct Trie));
    checkMalloc(trie);
    trie->dataSize = dataSize;
    trie->root = createTrieNode(trie, NULL);
    trie->nodeCount = 0;
    trie->root->isRoot = true;
    return trie;
}

void insertByLetter(Trie trie, void *data) {
    char *word = (char *)data;
    int wordLength = strlen(word);
    char *endOfWord = malloc(2);
    checkMalloc(endOfWord);
    *endOfWord = '$';
    *(endOfWord + 1) = '\0';
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
                char *data = malloc(2);
                checkMalloc(data);
                *data = word[j];
                *(data + 1) = '\0';
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
void BFSPrint(Trie trie, FILE *file) {
    if (file == NULL)
        return;
    // pointer la un vector de structuri TrieNode
    TrieNode** queue = malloc(trie->nodeCount * sizeof(TrieNode*));
    checkMalloc(queue);
    memset(queue, 0, trie->nodeCount * sizeof(TrieNode *));
    int front = 0;
    int rear = 0;

    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        if (trie->root->children[i] != NULL) {
            queue[rear++] = trie->root->children[i];
        }
    }
    //marchez sfarsitul randului cu NULL
    queue[rear++] = NULL;

    while (front != rear) {
        TrieNode *node = queue[front++];
        if (node == NULL) {
            fprintf(file, "\n");
            if (front != rear) {
                if (rear == trie->nodeCount) {
                    queue = realloc(queue, trie->nodeCount * 2 * sizeof(TrieNode*));
                    checkMalloc(queue);
                }
                queue[rear++] = NULL;
            }
        } else {
            fprintf(file, "%s ", (char *)node->data);
            for (int i = 0; i < CHILDREN_NUMBER; i++) {
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
    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        if (node->children[i] != NULL) {
            if (node->children[i]->data != NULL) {
                if (*(char *)node->children[i]->data == '$')
                    (*numberOfLeafs)++;
            }
            countLeafs(node->children[i], numberOfLeafs);
        }
    }
}

void getNumberOfLeafs(TrieNode *root, int *numberOfLeafs, FILE *file) {
    if (file == NULL)
        return;
    if (root->isRoot)
        countLeafs(root, numberOfLeafs);
    else {
        fprintf(file, "You need to give me the root of the tree.");
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
    for (int i = 0; i < CHILDREN_NUMBER; i++) {
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

void getNumberOfKSuffixes(TrieNode *root, int k, int *numberOfLetters,
                          int *numberOfSuffixes, FILE *file) {
    if (file == NULL)
        return;
    if (root->isRoot) {
        *numberOfLetters = 0;
        *numberOfSuffixes = 0;
        countSuffixes(root, k, numberOfLetters, numberOfSuffixes);
    }
    else {
        fprintf(file, "You need to give me the root of the tree.");
        return;
    }
}

void countChildren(TrieNode *node, int *maxChildren) {
    if (node == NULL)
        return;
    
    int cntr = 0;
    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        if (node->children[i] != NULL) {
            cntr++;
        }
    }

    if (cntr > *maxChildren) 
        *maxChildren = cntr;

    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        if (node->children[i] != NULL) {
           countChildren(node->children[i], maxChildren);
        }
    }
}

void getMaxNumberOfChildren(TrieNode *root, int *maxChildren, FILE *file) {
    if (file == NULL)
        return;
    if (root->isRoot) {
        *maxChildren = 0;
        countChildren(root, maxChildren);
    } else {
        fprintf(file, "You need to give me the root of the tree.");
        return;
    }
}

void searchSuffix(TrieNode *node, char *word, int *i, FILE *file) {
    if (node == NULL || word == NULL || file == NULL)
        return;
    if (*i == strlen(word)) {
        if (node->children[0] != NULL) {
            fprintf(file, "1\n");
            return;
        } else {
            fprintf(file, "0\n");
            return;
        } 
    }
    for (int j = 0; j < CHILDREN_NUMBER; j++) {
        if (node->children[j] != NULL) {
            if (node->children[j]->data != NULL) {
                if (*(char *)node->children[j]->data == word[*i]) {
                    (*i)++;
                    searchSuffix(node->children[j], word, i, file);
                    return;
                }
            }
        }
    }
    fprintf(file, "0\n");
}

void makeCompactTrie(Trie trie, char *data) {
    if (trie == NULL || data == NULL)
        return;
    if (trie->dataSize != sizeof(char *)) {
        printf("Nu ai definit o trie cu suficient "
        "spatiu in noduri pentru a fi compacta.\n");
        return;
    }
    char *word = (char *)data;
    int wordLength = strlen(word);
    char *endOfWord = malloc(2);
    checkMalloc(endOfWord);
    *endOfWord = '$';
    *(endOfWord + 1) = '\0';
    // daca trie-ul e gol, voi adauga direct $ care va ramane
    // acolo pe toata durata de viata a trie-ului deoarece
    // fiecare cuvant are un $ la sfarsit
    if (trie->root->children[0] == NULL) {
        trie->root->children[0] = createTrieNode(trie, endOfWord);
        trie->nodeCount++;
    }
    for (int i = wordLength - 1; i >= 0; i--) {
        // plec din root
        TrieNode *node = trie->root;
        int lenDataNode = 0;
        char *suffix = word + i;
        int firstLetter = suffix[0] - 'a' + 1;
        if (node->children[firstLetter] == NULL) {
            node->children[firstLetter] = createTrieNode(trie, suffix);
            node->children[firstLetter]->parent = node;
            trie->nodeCount++;
        } else {
            while (node->children[firstLetter] != NULL) {
                node = node->children[firstLetter];
                lenDataNode = strlen((char *)node->data);
                suffix = suffix + lenDataNode;
                firstLetter = suffix[0] - 'a' + 1;
            }
            if (suffix[0] != '\0') {
                node->children[firstLetter] = createTrieNode(trie, suffix);
                node->children[firstLetter]->parent = node;
                trie->nodeCount++;
            }
        }
        node = node->children[firstLetter];
        if (node->children[0] == NULL) {
            node->children[0] = createTrieNode(trie, endOfWord);
            trie->nodeCount++;
        }
    }
    free(endOfWord);
}

void destoryTrie(Trie trie) {
    TrieNode** queue = malloc(trie->nodeCount * sizeof(TrieNode*));
    checkMalloc(queue);
    memset(queue, 0, trie->nodeCount * sizeof(TrieNode*));
    int front = 0;
    int rear = 0;

    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        if (trie->root->children[i] != NULL) {
            queue[rear++] = trie->root->children[i];
        }
    }

    while (front != rear) {
        TrieNode *node = queue[front++];
        if (node->data != NULL) {
            free(node->data);
        }
        for (int i = 0; i < CHILDREN_NUMBER; i++) {
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include "utils.h"
#define STANDARD_WORD_LENGTH 101

void readData(Trie trie, char *data, FILE *input, void (*insertFunc)(Trie trie, void *data)) {
    int n;
    fscanf(input, "%d", &n);
    fgetc(input);
    while (n) {
        data[0] = '\0';
        if (fgets(data, STANDARD_WORD_LENGTH, input) != NULL) {
            data[strcspn(data, "\n")] = '\0';
            insertFunc(trie, data);
        }
        n--;
    }
}

int main(int argc, char *argv[]) {
    char *data = malloc(STANDARD_WORD_LENGTH);
    char task[5] = "";
    checkMalloc(data);
    checkMalloc(task);
    FILE *input = NULL;
    FILE *output = NULL;
    int k = 0;

    if (argc == 4) {
        printf("c1 c3 c4");
        input = fopen(argv[2], "r");
        checkFile(input);
        output = fopen(argv[3], "w");
        strcpy(task, argv[1]);
    } else if (argc == 5) {
        input = fopen(argv[3], "r");
        checkFile(input);
        output = fopen(argv[4], "w");
        strcpy(task, argv[1]);
        k = atoi(argv[2]);
    }

    if (strcmp(task, "-c1") == 0) {
        Trie trie = createTrie(sizeof(char));
        checkMalloc(trie);

        readData(trie, data, input, insertByLetter);

        BFSPrint(trie, output);
        destoryTrie(trie);
    } else if (strcmp(task, "-c2") == 0) {
        Trie trie = createTrie(sizeof(char));
        checkMalloc(trie);

        int numberOfLeafs = 0;
        int numberOfLetters = 0;
        int numberOfSuffixes = 0;
        int maxNumberOfChildern = 0;

        readData(trie, data, input, insertByLetter);

        getNumberOfLeafs(trie->root, &numberOfLeafs, output);
        getNumberOfKSuffixes(trie->root, k, &numberOfLetters,
                             &numberOfSuffixes, output);
        getMaxNumberOfChildren(trie->root, &maxNumberOfChildern, output);

        fprintf(output, "%d\n%d\n%d\n", numberOfLeafs, numberOfSuffixes,
                maxNumberOfChildern);
        
        destoryTrie(trie);
    } else if (strcmp(task, "-c3") == 0) {
        Trie trie = createTrie(sizeof(char));
        checkMalloc(trie);

        int n;
        int m;
        fscanf(input, "%d %d", &n, &m);
        fgetc(input);
        while (n) {
            data[0] = '\0';
            if (fgets(data, STANDARD_WORD_LENGTH, input) != NULL) {
                data[strcspn(data, "\n")] = '\0';
                insertByLetter(trie, data);
            }
            n--;
        }
        while (m) {
            data[0] = '\0';
            if (fgets(data, STANDARD_WORD_LENGTH, input) != NULL) {
                data[strcspn(data, "\n")] = '\0';
                int i = 0;
                searchSuffix(trie->root, data, &i, output);
            }
            m--;
        }
        destoryTrie(trie);
    } else if (strcmp(task, "-c4") == 0) {
        Trie trie = createTrie(sizeof(char *));
        checkMalloc(trie);

        readData(trie, data, input, insertByLetter);
        transformInCompactTrie(trie, trie->root);

        BFSPrint(trie, output);
        destoryTrie(trie);
    }
    
    free(data);
    if (input != NULL) {
        fclose(input);
    }
    if (output != NULL) {
        fclose(output);
    }
}
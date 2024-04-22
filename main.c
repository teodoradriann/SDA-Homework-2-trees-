#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    FILE* input = fopen("input.txt", "r");
    checkFile(input);
    FILE* output = fopen("output.txt", "w");
    Trie trie = createTrie(sizeof(char *));

    makeCompactTrie(trie, "banana");
    BFSPrint(trie, output);
    destoryTrie(trie);
    fclose(output);
}
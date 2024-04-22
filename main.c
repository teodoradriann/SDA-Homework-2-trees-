#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie(sizeof(char *));
    FILE* output = fopen("output.txt", "w");
    makeCompactTrie(trie, "banana");
    BFSPrint(trie, output);
    destoryTrie(trie);
    fclose(output);
}
#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie();
    FILE* output = fopen("output.txt", "w");
    insert(trie, "banana");
    BFSPrint(trie, output);
    destoryTrie(trie);
    fclose(output);
}
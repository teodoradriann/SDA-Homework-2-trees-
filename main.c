#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie();
    insert(trie, "banana");
    BFSPrint(trie);
    int i = 0;
    findSuffix(trie->root, "ana", &i, NULL);
    destoryTrie(trie);
}
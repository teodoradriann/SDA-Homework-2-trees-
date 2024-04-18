#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie();
    int numberOfLeafs = 0;
    insert(trie, "banana");
    getNumberOfLeafs(trie->root, &numberOfLeafs);
    printf("%d", numberOfLeafs);
    //BFSPrint(trie);
    destoryTrie(trie);
}
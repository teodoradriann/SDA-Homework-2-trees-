#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main() {
    Trie trie = createTrie();
    insert(trie, "banana");
    BFSPrint(trie);
    destoryTrie(trie);
}
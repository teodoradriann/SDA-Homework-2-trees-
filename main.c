#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie();
    //int numberOfLeafs = 0;
    insert(trie, "banana");
    int k = 3;
    int numberOfLetters;
    int numberOfSuffixes;
    getNumberOfKSuffixes(trie->root, k, &numberOfLetters, &numberOfSuffixes);
    printf("%d", numberOfSuffixes);
    //BFSPrint(trie);
    destoryTrie(trie);
}
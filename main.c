#include <stdio.h>
#include "trie.h"
#include "utils.h"

int main() {
    Trie trie = createTrie();
    //int numberOfLeafs = 0;
    insert(trie, "banana");
    insert(trie, "papuc");
    insert(trie, "bicicleta");
    insert(trie, "casa");
    insert(trie, "spalatorie");
    insert(trie, "baiat");
    insert(trie, "fata");
    insert(trie, "pusca");
    insert(trie, "programator");
    insert(trie, "smecher");
    insert(trie, "latitudine");
    insert(trie, "geografie");
    insert(trie, "informatica");
    insert(trie, "astronaut");
    insert(trie, "paralelipiped");
    insert(trie, "romana");
    insert(trie, "biologie");
    insert(trie, "google");
    insert(trie, "apple");
    insert(trie, "macbook");
    insert(trie, "iphone");
    insert(trie, "tigan");
    insert(trie, "roman");
    insert(trie, "francez");
    insert(trie, "italian");
    insert(trie, "state");
    // int k = 3;
    // int numberOfLetters;
    // int numberOfSuffixes;
    // getNumberOfKSuffixes(trie->root, k, &numberOfLetters, &numberOfSuffixes);
    // printf("%d", numberOfSuffixes);
    BFSPrint(trie);
    destoryTrie(trie);
}
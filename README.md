This is my implementation for the second homework project of Data Structures and Algorithms.

I chose to increase the difficulty of the assignment by using generic void * data types to further solidify my understanding. I decided to modularize my code as much as possible to make it easy to read and understand, with each part of the program having its own function/file. I believe my approach stands out from other assignments due to these strategies, plus the fact that every variable is dynamically allocated, and memory is used very efficiently.

In main.c, I only handle reading from files and data processing.
In train.c, I have all the functions that deal with trie management.
In utils.c, I have functions that I use frequently to check dynamic allocations or the existence of files.

Task 1

I implemented Task 1 using a simple method where I started iterations from the end of the word and created a new node for each suffix letter that wasn’t already in the trie. If I found a letter that already existed, I traversed the trie up to that point. For printing the trie, I used a classic BFS, utilizing a queue that I dynamically allocated based on the number of leaves the trie had, and I expanded it as needed because I also had to add \n.

Task 2

For each subtask, I used recursive implementations to traverse the trie and check each requirement. I implemented it in such a way that the user is not allowed to use a different starting node other than the root.

Task 3

For the implementation of Task 3, I also used a recursive method in which I searched for each suffix letter in the nodes and updated the index of the letter. If i was as long as the word and the node I was in contained $, it meant that I had found that suffix.

Task 4

For Task 4, I initially tried an implementation that directly created the compact trie. However, I realized this method was not feasible because, if I had the word “apple” (a word that in my method I would have added directly as a word), and then a suffix “ar” was added, I would have had to split “apple” into “a-pple” to add “a-r,” which would have been much more difficult to do. With this in mind, I decided to change my approach and started traversing each branch of the trie, looking for a node that wasn’t the end of a word and that had only one child. I then concatenated the child to the respective node and transferred the child node’s vector of children to the parent node. After that, I recursively started again from the larger node, searching for another child.


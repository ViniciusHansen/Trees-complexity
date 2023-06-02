# Complexity Analysis of AVL, RB, and B Trees

This project aims to perform a comparative analysis of the complexity of data structures known as AVL Trees, Red-Black Trees (RB), and B Trees. The analysis will be conducted by inserting sets of random cases (considered as average case) and sets of ordered cases (considered as worst case). The number of operations performed and the execution time of the operations will be measured.
## Data Structures
### AVL Tree

An AVL Tree is a balanced binary search tree in which the maximum difference between the heights of the left and right subtrees of any node is 1. This ensures that the tree is always balanced and provides efficient search, insertion, and deletion time.
### Red-Black Tree (RB)

A Red-Black Tree is another balanced binary search tree that also maintains proper balance. The properties of Red-Black Trees ensure that the height of the tree is limited to O(log n), resulting in efficient performance for search, insertion, and deletion operations.
### B Tree

A B Tree is a balanced search tree data structure that allows more than one value to be stored in each node. It is particularly useful when it comes to storing large volumes of data on disk, as it reduces the number of read and write operations required. The height of a B Tree is proportional to the logarithm of the number of stored keys, resulting in efficient performance for search, insertion, and deletion operations.
## Execution

Run `./main.sh`


// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST= (bst_t*)malloc(sizeof(bst_t));
    if (myBST == NULL)
    {
        return NULL;
    }
    myBST->root = NULL;
    myBST->size = 0;

    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    if (t == NULL)
    {
        exit(1);
    }
    if (t->size == 0)
    {
        return 1;
    }

    return 0;
}

// Returns 1 if value is found in the tree, 0 otherwise.
// For NULL tree -- exit the program.
// It should run in O(log(n)) time.
int find_helper(bstnode_t* node, int value) {
    if (node == NULL)
    {
        return 0;
    }

    if (value == node->data)
    {
        return 1;
    } else if (value < node->data)
    {
        return find_helper(node->leftChild, value);
    } else if (value > node->data)
    {
        return find_helper(node->rightChild, value);
    }
    return 0;
}

int bst_find(bst_t * t, int value){
    if (t == NULL)
    {
        exit(1);
    }
    int result = 0;
    if (find_helper(t->root, value) == 1)
    {
        result = 1;
    }
    return result;
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
bstnode_t* makeNode(int item) {
    bstnode_t* newNode = (bstnode_t*)malloc(sizeof(bstnode_t));
    newNode->data = item;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

int add_helper(bstnode_t* node, bstnode_t* newNode) {
    if (newNode->data < node->data)
    {
        if (node->leftChild == NULL)
        {
            node->leftChild = newNode;
        } else {
            add_helper(node->leftChild, newNode);
        }
    } else if (newNode->data > node->data)
    {
        if (node->rightChild == NULL)
        {
            node->rightChild = newNode;
        } else {
            add_helper(node->rightChild, newNode);
        }
    }
    return 1;
}

int bst_add(bst_t* t, int item){
    if (t == NULL)
    {
        return -1;
    }

    // so in my implementation, I first search whether the item has already in the tree
    // if the item is in the tree, we do not add duplicates
    if (bst_find(t, item) == 1)
    {
        return -1;
    }

    bstnode_t* newNode =  makeNode(item);

    if (t->root == NULL)
    {
        t->root = newNode;
        t->size++;
        return 1;
    }

    add_helper(t->root, newNode);
    t->size++;

    return 1;
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void print_helper(bstnode_t* node, int order) {
    if (node == NULL)
    {
        return;
    }
    if (order == 0)
    {
        print_helper(node->leftChild, order);
        printf("%d ", node->data);
        print_helper(node->rightChild, order);
    } else {
        print_helper(node->rightChild, order);
        printf("%d ", node->data);
        print_helper(node->leftChild, order);
    }
}

void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    } else{
        print_helper(t->root, order);
        printf("\n");
    }
}

// Returns the sum of all the nodes in the bst.
// A BST that is NULL exits the program.
// It should run in O(n) time.
int sum_helper(bstnode_t* node) {
    int sum = 0;
    int sum_left = 0;
    int sum_right = 0;
    if (node != NULL)
    {
        sum_left = sum_helper(node->leftChild);
        sum_right = sum_helper(node->rightChild);
        sum = node->data + sum_left + sum_right;
        return sum;
    }
    return sum;
}

int bst_sum(bst_t *t){
    if (t == NULL)
    {
        exit(1);
    }

    int result = sum_helper(t->root);
    return result;
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL)
    {
        exit(1);
    }
    return t->size;
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_helper(bstnode_t* node) {
    if (node == NULL)
    {
        return;
    }
    if (node->leftChild != NULL)
    {
        free_helper(node->leftChild);
    }
    if (node->rightChild != NULL)
    {
        free_helper(node->rightChild);
    }
    free(node);
}

void bst_free(bst_t* t){
    free_helper(t->root);
    free(t);
}

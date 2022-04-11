// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Create your node_t type here


// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

typedef struct node {
    int year;
    int numOfWins;
    struct node* next;
}node_t;



node_t* create_list(int year, int numOfWins) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
    	return NULL;
    }
    new_node->year = year;
    new_node->numOfWins = numOfWins;
    return new_node;
}

void print_list(node_t* node) {
    if (node == NULL) {
	return;
    }
    while (node != NULL) {
	printf("%d, %d wins\n", node->year, node->numOfWins);
        node = node->next;
    }
    printf("\n");
}

void free_list(node_t* node) {
    if (node == NULL) {
	return;
    }
    free(node);
}

int main(){
    // TODO: Implement me! 
    node_t* node1 = create_list(2018, 108);
    node_t* node2 = create_list(2017, 93);
    node_t* node3 = create_list(2016, 93);
    node_t* node4 = create_list(2015, 78);
    node_t* node5 = create_list(2014, 71);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = NULL;
	
    print_list(node1);
	
    free_list(node1);
    free_list(node2);
    free_list(node3);
    free_list(node4);
    free_list(node5);
		
    return 0;
}

// =================== Support Code =================
// Stack
//
//
//
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
//   - (i.e. stack_t* create_stack() should not have additional arguments)
// - You should not have any 'printf' statements in your stack functions. 
//   - (You may consider using these printf statements to debug, 
//      but they should be removed from your final version)
// ==================================================
#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
# define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	int count;		// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.
}stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
stack_t* create_stack(unsigned int capacity){
	// Modify the body of this function as needed.
	if (capacity > MAX_DEPTH)
	{
		capacity = MAX_DEPTH;
	}
	stack_t* myStack = (stack_t*)malloc(sizeof(stack_t));
	if (myStack == NULL)
	{
		return NULL;
	}
	myStack->count = 0;
	myStack->head = NULL;
	myStack->capacity = capacity;

	return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack_t* s){
	// TODO: Implement me!!
	if (s == NULL)
	{
		return -1;
	}
	
	if (s->count == 0)
	{
		return 1;
	}
	return 0;
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack_t* s){
	// TODO: Implement me!
	if (s == NULL)
	{
		return -1;
	}
	
	if (s->count == s->capacity)
	{
		return 1;
	}
	return 0;
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the Stack is full that is an error, but does not crash the program).
int stack_enqueue(stack_t* s, int item){
	// TODO: Implement me!
	if (stack_full(s) == 1)
	{
		return -1;
	}
	if (s== NULL)
	{
		return -1; // Note: you should have two return statements in this function.
	}
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
	{
		return -1;
	}

	if (stack_empty(s) == 1)
	{
		newNode->data = item;
		newNode->next = NULL;
		s->head = newNode;
		s->count++;
		return 0;
	}
	
	newNode->data = item;
	newNode->next = s->head;
	s->head = newNode;
	s->count++;
	
	return 0;
	
}

// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
// Removing from an empty stack should crash the program, call exit(1).
int stack_dequeue(stack_t* s){
	// TODO: Implement me!
	if (s == NULL)
	{
		exit(1);
	}
	if (stack_empty(s) == 1)
	{
		exit(1);
	}
	
	int item = s->head->data;
	node_t* temp = s->head;

	if (s->count == 1)
	{
		s->head = NULL;
		free(temp);
		s->count = 0;
		return item;
	}
	s->head = s->head->next;
	free(temp);
	s->count--;
	
	return item; // Note: This line is a 'filler' so the code compiles.
}

// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
// (i.e. A NULL stack cannot return the size)
unsigned int stack_size(stack_t* s){
	// TODO: Implement me!
	if (s == NULL)
	{
		exit(1);
	}
	
	return s->count;
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_stack(stack_t* s){
	// TODO: Implement me!
	if (s == NULL)
	{
		return;
	}

	node_t* temp = s->head;
	while (temp != NULL)
	{
		s->head = s->head->next;
		free(temp);
		temp = s->head;
	}
	free(s);
	
}

#endif

// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
// - Do NOT just replace this file with your DLL file - some of the 
//     signatures have changed data types! Our data is now a void*
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure. 
// NOTE THE CHANGES from your original node - we are using a 
// void pointer for data so that we can use the same dll 
// but we're not storing integers anymore.
typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;              // count keeps track of how many items are in the DLL.
    node_t* head;           // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.   
    dll_t* myDLL= (dll_t*)malloc(sizeof(dll_t));	

	if (myDLL == NULL)
	{
		return NULL;
	}

	myDLL->head = NULL;
	myDLL->tail = NULL;
	myDLL->count = 0;
        
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Exits if the DLL is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
    // TODO: Implement me!!
    if (l == NULL)
	{
		exit(1);
	} 
	if (l->count == 0)
	{
		return 1;
	} 

    return 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
    // TODO: Implement me!!
    if (l == NULL)
	{
		exit(1);
	}

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
	{
		return 0;
	}
	
	if (dll_empty(l) == 1)
	{
		newNode->data = item;
		newNode->next = NULL;
		newNode->previous = NULL;
		l->head = newNode;
		l->tail = newNode;
		l->count++;

		return 1;
	}

	node_t* temp = l->head;

	newNode->data = item;
	newNode->next = l->head;
	newNode->previous = NULL;
	temp->previous = newNode;
	l->head = newNode;
	l->count++;

	return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
    // TODO: Implement me!!
    if (l == NULL)
	{
		exit(1);
	}
	
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
	{
		return 0;
	}

	if (dll_empty(l) == 1)
	{
		newNode->data = item;
		newNode->next = NULL;
		newNode->previous = NULL;
		l->head = newNode;
		l->tail = newNode;
		l->count++;

		return 1;
	}

	node_t* temp = l->tail;

	newNode->data = item;
	newNode->previous = l->tail;
	newNode->next = NULL;
	temp->next = newNode;
		
	l->tail = newNode;
	l->count++;

	return 1; 
}

// Returns the first item in the DLL and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
    // TODO: Implement me!!
    if (t == NULL)
	{
		exit(1);
	}

	if (dll_empty(t) == 1)
	{
		return NULL;
	}

	node_t* oldHead = t->head;
	void* item = oldHead->data;

	if (t->count == 1)
	{
		t->head = NULL;
		t->tail = NULL;
		free(oldHead);
		t->count--;
		return item;
	} 
	t->head = oldHead->next;
	free(oldHead);

	node_t* newHead = t->head;
	newHead->previous = NULL;
	
	t->count--;
	return item;
}

// Returns the last item in the DLL, and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
    // TODO: Implement me!!
    if (t == NULL)
	{
		exit(1);
	}
	if (dll_empty(t) == 1)
	{
		return NULL;
	}

	node_t* oldTail = t->tail;
	void* item = oldTail->data;

	if (t->count == 1)
	{
		t->head = NULL;
		t->tail = NULL;
		t->count--;
		free(oldTail);
		return item;	
	} 
	t->tail = oldTail->previous;
	free(oldTail);

	node_t* newTail = t->tail;
	newTail->next = NULL;
		
	t->count--;
	return item; 
}

// Inserts a new node before the node at the specified position.
// Exits if the DLL is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
    // TODO: Implement me!!
    if (l == NULL) {
		exit(1);
	}
	if (pos < 0 || pos > l->count) {
		return 0;
	}
	if (pos == 0 || dll_empty(l) == 1) {
		return dll_push_front(l, item);
	}
	if (pos == l->count) {
		return dll_push_back(l, item);
	}
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) {
		return 0;
	}
	newNode->data = item;
	
	node_t* prevNode = l->head;
	int i;
	for (i = 0; i < pos - 1; i++) {
		prevNode = prevNode->next;
	}
	
	node_t* nextNode = prevNode->next;
	newNode->previous = prevNode;
	newNode->next = nextNode;
	nextNode->previous = newNode;
	prevNode->next = newNode;
	l->count++;

	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
    // TODO: Implement me!!
    if (l == NULL) {
		exit(1);
	}
	if (pos < 0 || pos >= l->count) {
		return NULL;
	}
	node_t* temp = l->head;
	int i;
	for (i = 0; i < pos; i++) {
		temp = temp->next;
	}
	return temp->data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
    // TODO: Implement me!!
    if (l == NULL) {
		exit(1);
	}	
	if (pos < 0 || pos >= l->count || dll_empty(l) == 1) {
		return NULL;
	}
	if (pos == 0) {
		return dll_pop_front(l);
	}
	if(pos == l->count - 1) {
		return dll_pop_back(l);
	}
	
	node_t* removedNode = l->head;
	int i;
	for (i = 0; i < pos; i++) {
		removedNode = removedNode->next;
	}
	void* item = removedNode->data;
	node_t* prevNode = removedNode->previous;
	node_t* nextNode = removedNode->next;
	
	prevNode->next = nextNode;
	nextNode->previous = prevNode;
	free(removedNode);
	l->count--;

	return item; 
}

// DLL Size
// Exits if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
    // TODO: Implement me!!
    if (t == NULL)
	{
		exit(1);
	}
	
	return t->count;; // Note: This line is a 'filler' so the code compiles.
}

// Free DLL
// Exits if the DLL is NULL.
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    // TODO: Implement me!!    
    if (t == NULL) {
		return;
	}	
	
	node_t* currentNode = t->head;
	while (currentNode != NULL) { 
		node_t* nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;	
	}
	free(t);
}

#endif

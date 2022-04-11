// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
    int visited;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    if (myGraph == NULL)
    {
        return NULL;
    }
    
    myGraph->nodes = create_dll();
    if (myGraph->nodes == NULL)
    {
        free(myGraph);
        return NULL;
    }
    
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    if (g == NULL || g->numNodes == 0)
    {
        return NULL;
    }
    node_t* itr = g->nodes->head;
    int i;
    int size = dll_size(g->nodes);
    for ( i = 0; i < size; i++)
    {
        graph_node_t* node = (graph_node_t*)itr->data;
        if (node != NULL)
        {
            if (node->data == value)
            {
            return node;
            }
        }
        itr = itr->next;
    }
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    if (graph_node->inNeighbors == NULL)
    {
        free(graph_node->inNeighbors);
        free(graph_node);
        return NULL;
    }
    
    graph_node->outNeighbors = create_dll();
    if (graph_node->outNeighbors == NULL)
    {
        free(graph_node->outNeighbors);
        free(graph_node);
        return NULL;
    }
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    // https://www.tutorialspoint.com/c_standard_library/c_macro_assert.htm
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// helper function to find the index of a node in a dll
// such that the index can be used in the dll_remove function
int index_finder(dll_t* l, void* data) {
    if (l == NULL)
    {
        return -1;
    }
    node_t* itr = l->head;
    int index = 0;
    while (itr != NULL && itr->data != data)
    {
        itr = itr->next;
        index++;
    }
    if (index == dll_size(l))
    {
        return -1;
    }
    return index;
}

dll_t* getInNeighbors( graph_t * g, int value );
dll_t* getOutNeighbors( graph_t * g, int value );
int getNumInNeighbors( graph_t * g, int value);
int getNumOutNeighbors( graph_t * g, int value);
// helper function to free memory after removing a node
void free_helper(graph_t* g, graph_node_t* node) {
    if (node->inNeighbors != NULL)
    {
        free_dll(node->inNeighbors);
    }
    if (node->outNeighbors != NULL)
    {
        free_dll(node->outNeighbors);
    }
    int index = index_finder(g->nodes, node);
    dll_remove(g->nodes, index);
    free(node);
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // TODO: Implement me!
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    if (g == NULL)
    {
        return -1;
    }

    graph_node_t* node_tobe_removed = find_node(g, value);
    if (node_tobe_removed == NULL)
    {
        return 0;
    }
    
    // remove the node from all its outNeighbors' inNeighbors
    // 1. get all the out neighbors of this node
    dll_t* allOutNeighbors = getOutNeighbors(g, value);
    // 2. remove this node from all the out neighbors' in neighbors
    // 2.1 assign an iterator to be iterated over all the out neighbors
    node_t* itr_outNeighbors = allOutNeighbors->head;
    // 2.2 loop over all the out neighbors of this node, 
    // for each out neighbor, find the position of this node and remove it from the out neighbor's in neighbor
    while (itr_outNeighbors != NULL)
    {
        graph_node_t* outNeighbor = (graph_node_t*)itr_outNeighbors->data;
        int index = index_finder(outNeighbor->inNeighbors, node_tobe_removed);
        dll_remove(outNeighbor->inNeighbors, index);
        itr_outNeighbors = itr_outNeighbors->next;
    }

    // remove the node from all its inNeighbors' outNeighbors
    // 1. get all the in neighbors of this node
    dll_t* allInNeighbors = getInNeighbors(g, value);
    // 2. remove this node from all the in neighbors' out neighbors
    // 2.1 assign an iterator to be iterated over all the in neighbors
    node_t* itr_inNeighbors = allInNeighbors->head;
    // 2.2 loop over all the in neighbors of this node, 
    // for each in neighbor, find the position of this node and remove it from the in neighbor's out neighbor
    while (itr_inNeighbors != NULL)
    {
        graph_node_t* inNeighbor = (graph_node_t*)itr_inNeighbors->data;
        int index = index_finder(inNeighbor->outNeighbors, node_tobe_removed);
        dll_remove(inNeighbor->outNeighbors, index);
        itr_inNeighbors = itr_inNeighbors->next;
    }

    int numNodeEdge = 0;
    int numEdgeIn = getNumInNeighbors(g, value);
    int numEdgeOut = getNumOutNeighbors(g, value);
    if (numEdgeIn != -1)
    {
        numNodeEdge += numEdgeIn;
    }
    if (numEdgeOut != -1)
    {
        numNodeEdge += numEdgeOut;
    }

    free_helper(g, node_tobe_removed);    
    g->numNodes--;
    g->numEdges -= numNodeEdge;
    
    return 1;
}

int contains_edge( graph_t * g, int source, int destination);
// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if (g == NULL)
    {
        return -1;
    }
    if (contains_edge(g, source, destination) == 1)
    {
        return 0;
    }
    graph_node_t* src = find_node(g, source);
    graph_node_t* dest = find_node(g, destination);
    if (src == NULL || dest == NULL)
    {
        return 0;
    }
    dll_push_back(src->outNeighbors, dest);
    dll_push_back(dest->inNeighbors, src);
    g->numEdges++;
    
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if (g == NULL)
    {
        return -1;
    }
    if (contains_edge(g, source, destination) != 1)
    {
        return 0;
    }
    graph_node_t* src = find_node(g, source);
    graph_node_t* dest = find_node(g, destination);
    if (src == NULL || dest == NULL)
    {
        return 0;
    }

    // remove destination from outNeighbors of source
    int i;
    int outSize = dll_size(src->outNeighbors);
    for ( i = 0; i < outSize; i++)
    {
        graph_node_t* outNode = (graph_node_t*)dll_get(src->outNeighbors, i);
        if (outNode->data == destination)
        {
            dll_remove(src->outNeighbors, i);
            break;
        }
    }

    // remove source from inNeighbors of destination
    int inSize = dll_size(dest->inNeighbors);
    for ( i = 0; i < inSize; i++)
    {
        graph_node_t* inNode = (graph_node_t*)dll_get(dest->inNeighbors, i);
        if (inNode->data == source)
        {
            dll_remove(dest->inNeighbors, i);
            break;
        }
    }
    
    g->numEdges--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    // TODO: Implement me!
    if (g == NULL)
    {
        return -1;
    }
    graph_node_t* src = find_node(g, source);
    graph_node_t* dest = find_node(g, destination);
    if (src == NULL || dest == NULL)
    {
        return 0;
    }
    int i = 0;
    for (i = 0; i < src->outNeighbors->count; i++)
    {
        graph_node_t* node = (graph_node_t*)dll_get(src->outNeighbors, i);
        if (node->data == dest->data)
        {
            return 1;
        }
    }
    return 0;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    if (g == NULL)
    {
        return NULL;
    }
    
    graph_node_t* node = find_node(g, value);
    if (node == NULL)
    {
        return NULL;
    }
    return node->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    if (g == NULL)
    {
        return -1;
    }
    
    graph_node_t* node = find_node(g, value);
    if (node == NULL)
    {
        return -1;
    }
    return dll_size(node->inNeighbors);
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    if (g == NULL)
    {
        return NULL;
    }
    
    graph_node_t* node = find_node(g, value);
    if (node == NULL)
    {
        return NULL;
    }
    return node->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    if (g == NULL)
    {
        return -1;
    }
    
    graph_node_t* node = find_node(g, value);
    if (node == NULL)
    {
        return -1;
    }
    return dll_size(node->outNeighbors);
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    // TODO: Implement me!
    if (g == NULL)
    {
        return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    // TODO: Implement me!
    if (g == NULL)
    {
        return -1;
    }
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    // TODO: Implement me!
    if (g == NULL)
    {
        return;
    }
    node_t* itr = g->nodes->head;
    node_t* temp;
    int i;
    for(i = 0; i < g->numNodes; i++) {
        temp = itr->next;
        free_helper(g, itr->data);
        itr = temp;
    }
    free_dll(g->nodes);
    free(g);
}

// IMPLEMENT THESE AFTER ALL THE FUNCTIONS ABOVE ARE --TESTED--
// AND CONFIRMED TO WORK
// Reference: https://www.programiz.com/dsa/graph-bfs
// helper function to initialize all the graph nodes->visited as unvisited (0)
void reset(graph_t* g) {   
    int i;
    int graphNodesSize = dll_size(g->nodes);
    for ( i = 0; i < graphNodesSize; i++)
    {
        graph_node_t* node = (graph_node_t*)dll_get(g->nodes, i);
        node->visited = 0;
    }
}

// BFS implementation
dll_t* bfs(graph_t* g, int value) {
    if (g == NULL)
    {
        return NULL;
    }
    reset(g);
    dll_t* nodesVisited = create_dll();
    dll_t* queue = create_dll();
    graph_node_t* root = find_node(g, value);
    root->visited = 1;
    dll_push_back(queue, root);
    int i;
    while (dll_empty(queue) != 1) {
        graph_node_t* currentNode = (graph_node_t*)dll_pop_front(queue);
        dll_push_back(nodesVisited, currentNode);
        int currentNodeOutNeighborsSize = dll_size(currentNode->outNeighbors);
        for ( i = 0; i < currentNodeOutNeighborsSize; i++)
        {
            graph_node_t* outNeighbor = (graph_node_t*)dll_get(currentNode->outNeighbors, i);
            if (outNeighbor->visited == 0)
            {
                dll_push_back(queue, outNeighbor);
                outNeighbor->visited = 1;
            }
        }
    }
    free_dll(queue);
    return nodesVisited;
}
// returns 1 if we can reach the destination from source
// returns 0 if it is not reachable
// returns -1 if the graph is NULL (using BFS)
int graph_is_reachable(graph_t * g, int source, int dest){
    if (g == NULL)
    {
        return -1;
    }
    if (find_node(g, source) == NULL || find_node(g, dest) == NULL)
    {
        return 0;
    }
    int edgeFromSourceToDest = contains_edge(g, source, dest);
    int edgeFromDestToSource = contains_edge(g, dest, source);
    if ((source == dest) & ((edgeFromSourceToDest) == 1) & ((edgeFromDestToSource) == 1))
    {
        return 1;
    }
    
    dll_t* sourceBFS = bfs(g, source);
    int i;
    int bfsSize = dll_size(sourceBFS);
    for ( i = 0; i < bfsSize; i++)
    {
        graph_node_t* visitedNode = (graph_node_t*)dll_get(sourceBFS, i);
        if (visitedNode->data == dest)
        {
            free_dll(sourceBFS);
            return 1;
        }
    }
    free_dll(sourceBFS);
    return 0;
}

// returns 1 if there is a cycle in the graph
// returns 0 if no cycles exist in the graph
// returns -1 if the graph is NULL 
// You may use either BFS or DFS to complete this task.
int graph_has_cycle(graph_t * g){
    if (g == NULL)
    {
        return -1;
    }

    node_t* startNode = g->nodes->head;
    while (startNode != NULL)
    {
        graph_node_t* startGraphNode = (graph_node_t*)startNode->data;
        node_t* itr_outNeighbors = startGraphNode->outNeighbors->head;
        while (itr_outNeighbors != NULL)
        {
            graph_node_t* outNeighbor = (graph_node_t*)itr_outNeighbors->data;
            if (graph_is_reachable(g, outNeighbor->data, startGraphNode->data) == 1) {
                return 1;
            }
            itr_outNeighbors = itr_outNeighbors->next;
        }
        startNode = startNode->next;
    }
    return 0;
}

// helper function for print_path
void print_helper(graph_t* g, graph_node_t* sourceNode, int dest, dll_t*stack) {
    if (g == NULL)
    {
        return;
    }
    if(sourceNode == NULL) {
        return;
    }

    reset(g);
    dll_push_back(stack, &sourceNode->data);
    if(sourceNode->data == dest) {
        node_t* root = stack->head;
        printf("The path is in the order from left to right below:\n");
        while(root != NULL) {
            printf("%d ", *((int*)(root->data)));
            root = root->next;
        }
        printf("\n");
        sourceNode->visited = 1;
        return;
    }
    node_t* itr = sourceNode->outNeighbors->head;
    while(itr != NULL) {
        graph_node_t* itr_graph_node = (graph_node_t*)(itr->data);
        if( itr_graph_node->visited == 0) {
            print_helper(g, itr_graph_node, dest, stack);     
        }
        itr = itr->next;
    }
    dll_pop_back(stack);
}
// prints any path from source to destination if there 
// exists a path from the source to the destination.
// Note: Consider using one of the other functions to help you
//       determine if a path exists first
// (Choose either BFS or DFS, typically DFS is much simpler)
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from a source to destination
// Returns -1 if the graph is NULL
int graph_print_path(graph_t * g, int source, int dest){
    if (g == NULL)
    {
        return -1;
    }
    if (graph_is_reachable(g, source, dest)!= 1)
    {
        return 0;
    }
    if (find_node(g, source) == NULL|| find_node(g, dest) == NULL)
    {
        return 0;
    }
    graph_node_t* sourceNode = find_node(g, source);
    dll_t* stack = create_dll();
    print_helper(g, sourceNode, dest, stack);
    free_dll(stack);
    return 1;
}

#endif

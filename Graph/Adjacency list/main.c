// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {
    printf("==================================================\n");
    printf("======Test add_node, find_node and num_nodes======\n");
    printf("==================================================\n");
    graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 1);
    printf("find node 1 == %d\n", find_node(graph, 1)->data);
    graph_add_node(graph, 2);
    graph_add_node(graph, 2);
    printf("find node 2 == %d\n", find_node(graph, 2)->data);
    graph_add_node(graph, 3);
    printf("find node 3 == %d\n", find_node(graph, 3)->data);
    graph_add_node(graph, 4);
    printf("find node 4 == %d\n", find_node(graph, 4)->data);
    graph_add_node(graph, 5);
    printf("find node 5 == %d\n", find_node(graph, 5)->data);
    printf("total nodes: 5==%d\n", graph_num_nodes(graph));

    printf("======================================================\n");
    printf("======Test add_edge, contains_edge and num_edges======\n");
    printf("======================================================\n");

    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 1, 5);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 2, 5);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 5);
    graph_add_edge(graph, 5, 1);    
    printf("Total number of edges: 9==%d\n", graph_num_edges(graph));
    printf("Try to add a duplicate edge 1->2: 0==%d\n", graph_add_edge(graph, 1, 2));
    printf("Try to add a duplicate edge 3->4: 0==%d\n", graph_add_edge(graph, 3, 4));
    printf("If graph contains edge 1->3: 1==%d\n", contains_edge(graph, 1, 3));
    printf("If graph contains edge 5->1: 1==%d\n", contains_edge(graph, 5, 1));

    printf("======================================================\n");
    printf("============Test remove_edge and num_edges============\n");
    printf("======================================================\n");
    graph_remove_edge(graph, 1, 4);
    printf("Total number of edges: 8==%d\n", graph_num_edges(graph));
    printf("If graph contains edge 1->4: 0==%d\n", contains_edge(graph, 1, 4));
    graph_remove_edge(graph, 2, 5);
    printf("Total number of edges: 7==%d\n", graph_num_edges(graph));
    printf("If graph contains edge 2->5: 0==%d\n", contains_edge(graph, 2, 5));

    printf("======================================================\n");
    printf("===================Test is_reachable==================\n");
    printf("======================================================\n");
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 2, 5);
    graph_add_node(graph, 6);
    printf("find node 6 == %d\n", find_node(graph, 6)->data);
    printf("total nodes: 6==%d\n", graph_num_nodes(graph));
    graph_add_edge(graph, 2, 6);
    graph_remove_edge(graph, 5, 1);
    printf("If node 5 is reachable from node 1: 1==%d\n", graph_is_reachable(graph, 1, 5));
    printf("If node 1 is reachable from node 5: 0==%d\n", graph_is_reachable(graph, 5, 1));
    printf("If node 5 is reachable from node 2: 1==%d\n", graph_is_reachable(graph, 2, 5));
    printf("If node 2 is reachable from node 1: 1==%d\n", graph_is_reachable(graph, 1, 2));
    printf("If node 4 is reachable from node 1: 1==%d\n", graph_is_reachable(graph, 1, 4));
    printf("If node 4 is reachable from node 2: 1==%d\n", graph_is_reachable(graph, 2, 4));
    printf("If node 6 is reachable from node 3: 0==%d\n", graph_is_reachable(graph, 3, 6));

    printf("======================================================\n");
    printf("=====================Test has_cycle===================\n");
    printf("======================================================\n");
    printf("If graph has cycle: 0==%d\n", graph_has_cycle(graph));
    printf("Add edge 5->1\n");
    graph_add_edge(graph, 5, 1);
    printf("If graph has cycle: 1==%d\n", graph_has_cycle(graph));
    printf("Remove edge 5->1 and check if there's no cycle in the graph\n");
    graph_remove_edge(graph, 5, 1);
    printf("If graph has cycle: 0==%d\n", graph_has_cycle(graph));
    printf("Add another three nodes that includes a cycle, but none of them connected with the other nodes\n");
    graph_t * graph2 = create_graph();
    graph_add_node(graph2, 1);
    graph_add_node(graph2, 2);
    graph_add_node(graph2, 8);
    graph_add_node(graph2, 9);
    graph_add_edge(graph2, 2, 8);
    graph_add_edge(graph2, 8, 9);
    graph_add_edge(graph2, 9, 2);
    printf("Check if there's a cycle (constructed by the three new nodes) in the graph: 1==%d\n", graph_has_cycle(graph2));
    
    printf("======================================================\n");
    printf("====================Test print_path===================\n");
    printf("======================================================\n");
    
    graph_print_path(graph, 2, 5);

    printf("======================================================\n");
    printf("===================Test remove_node===================\n");
    printf("======================================================\n");
    graph_add_edge(graph, 5, 1);
    printf("Try to remove a node that doesn't exist: 7\n");
    printf("The response: %d==0\n", graph_remove_node(graph, 7));
    printf("If graph contains edge 2->6: 1==%d\n", contains_edge(graph, 2, 6));
    printf("Number of node 6 in-neighbors before removing node 2: 1==%d \n", getNumInNeighbors(graph,6));
    printf("Number of node 3 in-neighbors before removing node 2: 2==%d \n", getNumInNeighbors(graph,3));
    printf("Number of node 5 in-neighbors before removing node 2: 3==%d \n", getNumInNeighbors(graph,5));
    printf("Number of node 1 out-neighbors before removing node 2: 4==%d \n", getNumOutNeighbors(graph,1));
    printf("Remove node 2------\n");
    graph_remove_node(graph, 2);
    printf("Try to find node 2 after removing it:\n");
    if(find_node(graph, 2) == NULL) {
        printf("node 2 successfully removed!\n");
    }else {
        printf("Node 2 still here!\n");
    }
    printf("Number of node 6 in-neighbors after removing node 2: 0==%d \n", getNumInNeighbors(graph,6));
    printf("Number of node 3 in-neighbors after removing node 2: 1==%d \n", getNumInNeighbors(graph,3));
    printf("Number of node 5 in-neighbors after removing node 2: 2==%d \n", getNumInNeighbors(graph,5));
    printf("Number of node 1 out-neighbors after removing node 2: 3==%d \n", getNumOutNeighbors(graph,1));

    printf("Total number of nodes: 5==%d \n", graph_num_nodes(graph));
    printf("Total number of edges: 6==%d \n", graph_num_edges(graph));
    
    printf("Remove all the nodes\n");
    graph_remove_node(graph, 1);
    printf("Total number of nodes after removing node 1: 4==%d \n", graph_num_nodes(graph));
    printf("Total number of edges after removing node 1: 2==%d \n", graph_num_edges(graph));
    graph_remove_node(graph, 3);
    printf("Total number of nodes after removing node 3: 3==%d \n", graph_num_nodes(graph));
    printf("Total number of edges after removing node 3: 1==%d \n", graph_num_edges(graph));
    graph_remove_node(graph, 4);
    printf("Total number of nodes after removing node 4: 2==%d \n", graph_num_nodes(graph));
    printf("Total number of edges after removing node 4: 0==%d \n", graph_num_edges(graph));
    graph_remove_node(graph, 5);
    printf("Total number of nodes after removing node 5: 1==%d \n", graph_num_nodes(graph));
    printf("Total number of edges after removing node 5: 0==%d \n", graph_num_edges(graph));
    graph_remove_node(graph, 6);
    printf("Total number of nodes after removing node 6: 0==%d \n", graph_num_nodes(graph));
    printf("Total number of edges after removing node 6: 0==%d \n", graph_num_edges(graph));

    free_graph(graph);
    free_graph(graph2);

    return 0;
}

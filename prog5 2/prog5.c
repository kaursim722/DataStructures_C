#include "Graph.h"
#include "List.h"
#include "PQueue.h"
#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Point {
    int x;
    int y;
} Point;

Point *create_point(int x, int y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

//Hint: The ListPtrs will store ints for bfs and a_star.
//      You need to define the dataCompare, dataPrinter and freeData functions here. 

int dataCompare() {
    
}
int dataPrinter() {

}
int freeData() {

}

/**
 * @brief Implements the bst algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr bfs(Graph *g, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform bfs traversal. Make sure to store who the parent of each node in your traversal is.
    // Mark visited nodes to maek sure not to visit them twice
    return NULL;
}

/**
 * @brief Implements the A* search algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param nodeArr Array of positions of the graph vertices on a 2d plane. Note this is a pointer to a contiguous array, where nodeArr[i] should correspond to node i in the graph. 
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr a_star(Graph *g, Point *nodeArr, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform a star traversal. Make sure to store who the parent of each node in your traversal is, and the path cost up to that node.
    return NULL;
}


int main(int argc, char* argv[]) {
    // argv[1] will tell you if to run bfs or a_star
    int algorithm = (strcmp(argv[1], "bfs") == 0) ? 0 : 1;
    char typestr[800];
    int coordx;
    int coordy;
    int tok;
    int int_change;
    ListPtr node_list = list_create(dataCompare, dataPrinter, freeData);
    ListPtr edges_list = list_create(dataCompare, dataPrinter, freeData);
    ListPtr path_list = list_create(dataCompare, dataPrinter, freeData);
    // stdin will contain your input
    fgets(typestr, 500, stdin);
    printf("%s", typestr);
    while(!feof(stdin)) {
        if(fgets(typestr, 500, stdin) != NULL) {
            typestr[strcspn(typestr, "\n")] = 0;
            tok = strtok(typestr, "\n");
            int_change = atoi(typestr);
            sscanf("%s", typestr);
            printf("%s\n", typestr);
        }
    }
    //Parse node locations + count number of nodes

    // Create graph

    //Parse and add graph edges

    //Parse start and end points and run through correct search algorithm
    //Print results to stdout

    //free Data structures
    return 0;
}
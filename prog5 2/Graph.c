#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Graph.h"

typedef struct Graph{
    int num_vertices;
    int num_edges;
    ListPtr *adjacency_list; // Is an array of ListPtrs for faster access
} Graph;

int graphCompare(void *dat1, void *dat2) {
    int *obj1 = (int *)dat1;
    int *obj2 = (int *)dat2;
    if (*obj1 == *obj2) {
        return 0;
    }
    else {
        return -1;
    }
}

int graphPrinter(void* obj) {
    int *dat1 = (int*)obj;
    printf("%p\n", dat1);
}

int graphFreeData(void* data) {
    free(data);
    data = NULL;
}

// Hints: You will need to implement a ListPtr DataCompare, DataPrinter and 
//        freeData for the lists used in the adjacency list. These will be ints.
//        You can copy this from the ones in prog5.c, but they should have different name to avoid a namesapce collision.
//TODO: Implement all functions from the header file.

Graph *graph_create(int numVertices) {
    Graph *grph = (Graph *)malloc(sizeof(Graph));
    //if(grph != NULL) {
    if (grph == NULL) {
        return grph;
    }
    grph -> num_vertices = numVertices;
    grph -> num_edges = 0;
    grph -> adjacency_list = calloc(grph -> num_vertices, sizeof(ListPtr*));
    for(int i = 0; i < grph -> num_vertices; i++) {
        grph -> adjacency_list[i] = list_create(graphCompare, graphPrinter, graphFreeData);
    }
    return grph;
}

void graph_destroy(Graph *g) {
    if (g != NULL) {
        for(int i =0; i < g -> num_vertices; i++) {
            list_destroy(g -> adjacency_list[i], true);
        }
        free(g -> adjacency_list);
        free(g);
        g = NULL;
    }
    else{
        return g;
    }
}

bool graph_add_edge(Graph *g, int v1, int v2) {
    int *obj1 = (int *)malloc(sizeof(int));
    int *obj2 = (int *)malloc(sizeof(int));
    int *temp_v2 = (int *)malloc(sizeof(int));
    *temp_v2 = v2;
    if(g == NULL) {
        return false;
    }
    if((v1 >= 0 && v1 <= g -> num_vertices) && (v2 >= 0 && v2 <= g -> num_vertices)) {
        int temp_len = list_length(g -> adjacency_list[v1]);
        int i=0;
        //int temp_get_ind = list_get_index(g -> adjacency_list[v1], i);
        for(i; i < temp_len; i++) {
            if(list_get_index(g -> adjacency_list[v1], i) == temp_v2) {
                return false;
            }
        }
        *obj1 = v1;
        *obj2 = v2;
        list_append(g -> adjacency_list[v1], obj2);
        list_append(g -> adjacency_list[v2], obj1);
        g -> num_edges += 1;
        return true;
    }
    else {
        return false;
    }
}

bool graph_add_nodes(Graph *g, int numVertices) {
    if(g != NULL) {
        int resize = g -> adjacency_list + numVertices;
        g -> adjacency_list = (ListPtr *)realloc(g-> adjacency_list, resize * sizeof(ListPtr));
        for (int i= g -> num_vertices; i < resize; i++) {
            g -> adjacency_list[i] = list_create(graphCompare, graphPrinter, graphFreeData);
        }
        g -> num_vertices += numVertices;
        return true;
    }
    else {
        return false;
    }
}

bool graph_remove_edge(Graph *g, int v1, int v2) {
    int *temp_v1 = (int *)malloc(sizeof(int));
    int *temp_v2 = (int *)malloc(sizeof(int));

    if((v1 >= 0 && v1 <= g -> num_vertices) && (v2 >= 0 && v2 <= g -> num_vertices)) {
        int i = 0;
        int counter = 0;
        int temp_len = list_length(g -> adjacency_list[v1]);
        int temp_get_ind = list_get_index(g -> adjacency_list[v1], i);
        for(i; i<temp_len; i++) {
            if((*(int*)temp_get_ind) == v2) {
                list_del_index(g -> adjacency_list[v1], i);
                counter += 1;
            }
        }
        int temp_len2 = list_length(g -> adjacency_list[v1]);
        //int temp_get_ind2 = list_get_index(g -> adjacency_list[v1], i);
        for(i=0; i < temp_len2; i++) {
            if((*(int*)list_get_index(g -> adjacency_list[v1], i)) == v1) {
                list_del_index(g -> adjacency_list[v2], i);
                counter += 1;
            }
        }
        if(counter == 2) {
            g -> num_edges -= 1;
            return true;
        }
    }
    else {
        return false;
    }
}

bool graph_has_edge(Graph *g, int v1, int v2) {
    int *temp_v1 = (int *)malloc(sizeof(int));
    int *temp_v2 = (int *)malloc(sizeof(int));
    *temp_v1 = v1;
    *temp_v2 = v2; 
    int i=0;
    if((v1 >= 0 && v1 <= g -> num_vertices) && (v2 >= 0 && v2 <= g -> num_vertices)) {
        
        if((list_find_element(g -> adjacency_list[v1], temp_v2) != -1)&& (list_find_element(g -> adjacency_list[v2], temp_v1) != -1)) {
            return true;
        }
        return false;
    }
    else {
        return false;
    }
}

ListPtr graph_get_neighbors(Graph *g, int vertex) {
    if(vertex > 0 && vertex < g -> num_vertices) {
        if(g -> adjacency_list[vertex] == NULL) {
            return NULL;
        }
        return g -> adjacency_list[vertex];
    }
    else {
        return NULL;
    }
}

int graph_num_vertices(Graph *g) {
    return g -> num_vertices;
}

int graph_num_edges(Graph *g) {
    return g -> num_edges;
} 
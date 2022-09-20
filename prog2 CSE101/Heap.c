// Implementation of (Min) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"
#include<math.h>

// TODO: Implement funcs for fetching parent and left/right child

int parent(int i) {                             // functions used in this file are implemented from the CSE101 textbook, intro to algorithms 3rd edition
    return (floor(i/2));
}       

int left(int i) {
    return (2*i);
}

int right(int i) {
    return ((2*i) + 1);
}

//------------------------------------------------------------------------

// TODO: Helper function for swapping A[i] and A[j] elements in an array

void swap(int* A, int i, int j) {       
    int swap_var = A[i];
    A[i] = A[j];
    A[j] = swap_var;
}

//------------------------------------------------------------------------

/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
- id: (pointer to) array of client id used for implementing the heap
*/

typedef struct Heap{
    int len;
    int size;
    int *array;
    int *id;
} Heap;


//------------------------------------------------------------------------

/* TODO: implement initializeHeap function which instantiates a heap using malloc.
It returns a pointer to the instantiated heap
*/

Heap* initializeHeap(int len, int h_size, int* arr, int* id) {          //call this function to create a heap
    Heap* obj = (Heap*)malloc(sizeof(Heap));
    obj -> len = len;
    obj -> size = h_size;
    obj -> array = arr;
    obj -> id = id;
    return obj;
}


//------------------------------------------------------------------------


/*  TODO: implement heap destructor that frees memory allocated to heap */

void destructHeap(Heap* h) {       
    free(h);
}

//------------------------------------------------------------------------

/* TODO: implement 'heapify' function, given a heap pointer and an index i
This function maintain (min) Heap property given an index i for heap h
*/

void heapify(Heap* h, int i) {                                          //used to sort the heap to ensure the minimum value stays at the top of the tree/parent
    int l = left(i);
    int r = right(i);
    int min;
    if ((l <= h -> size) && (h -> array[l] < h -> array[i])) {   
        min = l;
    }
    else {
        min = i;
    }
    if ((r < h -> size) && (h -> array[r] < h -> array[min])) {   
        min = r;
    }
    if (min != i) {
        swap(h -> array, i, min);                                      //whenever I make changes to array, make same changes to id 
        swap(h -> id, i, min);
        heapify(h, min);          
    }
}

//------------------------------------------------------------------------

/* TODO: implement array_to_heap function
You may use initializeHeap function for implementing this function
*/

Heap* array_to_Heap(int* A, int* id, int len, int size) {
    Heap *obj = initializeHeap(len, size, A, id);
    obj -> size = obj -> len;
    for (int i = (obj -> len)/2; i > 1; i--)    
        heapify(obj, i);
    return obj;
} 

//------------------------------------------------------------------------

/* TODO: implement utility functions:
- size(): returns the size field of a heap
- len(): returns the length field of a heap
*/

int size(Heap* h) {
    return h -> size;
}

int len(Heap* h) {
    return h -> len;
}

void printHeap(Heap* h) {
    for (int counter = 0; counter < h -> size; counter ++) {
        printf("%d ", h -> id[counter]);
    }
}
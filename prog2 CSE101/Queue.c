#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
// Implemeting Queue

/*
TODO: define the Queue structure using 'typedef struct Queue' - this queue holds integer values
the Queue struct has the following fields:
- head: corresponding to the head of the queue
- tail: indicating the tail of the queue
- length: length of the array used for implementing the queue
- count: number of elements in the queue
- array: (pointer to) the array used for implementing the queue
- id: (pointer to) the array of client id used for implementing the queue
*/

typedef struct Queue {          
    int head;
    int tail;
    int length;
    int count;
    int *array;
    int *id;
} Queue;


//------------------------------------------------------------------------

/*
TODO: implement the initializeQueue - this function instantiates the Queue struct using malloc and sets the values for the fields.
It returns a pointer to the instantiated Queue
*/

Queue* initializeQueue(int n, int* arr, int* id) {              // functions used in this file are implemented from the CSE101 textbook, intro to algorithms 3rd edition
    Queue* obj = (Queue*)malloc(sizeof(Queue));
    obj -> head = 0;
    obj -> tail = 0;
    obj -> length = n;
    obj -> count = 0;
    obj -> array = arr;
    obj -> id = id;
    return obj;
}


//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to Queue
*/

void destructQueue(Queue* q) {
    free(q);
}

//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and int service time 'ser' and adds 'ser' to queue
*/

void enqueue(Queue* q, int i, int ser) {
    if (q -> count > q -> length) {                     //check whether the number of elements is higher than the length 
        return;
    }
    else {
        q -> array[q -> tail] = ser;                    
        q -> id[q -> tail] = i;
        q -> tail = (q -> tail + 1) % q -> length;
        q -> count += 1;
    }
    
}

//------------------------------------------------------------------------

/* TODO: implement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the queue
*/

int dequeue(Queue* q) {                 
    int temp;
    if (q -> count <= 0) {                                  //error checking
        return;
    }
    else {
        temp = q -> id[q -> head];
        q -> head = (q -> head + 1) % q -> length;         
        q -> count -= 1;
        return temp;
    }
    
}

//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in order (head to tail)
*/

void printQueue(Queue* q) {                         
    if ((q -> count <= 0)) {                //check for empty queue
        return;
    }
    else {
        for(int counter = q -> head; counter < q -> tail+1; counter ++) {
            printf("%d ", q -> id[counter]);
        }
    }
}


//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the queue
*/

int count(Queue* q) {
    return q -> count;
}
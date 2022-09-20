#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Code to implement the functions in List.h

ListPtr newList(bool (*dataEqual)(void *obj1, void*obj2), void (*dataPrinter)(void *data), void (*freeData)(void *data)) {
    ListPtr new_list = malloc(sizeof(ListPtr));
    new_list -> dataPrinter = dataPrinter;
    new_list -> dataEqual = dataEqual;
    new_list -> freeData = freeData;
    new_list -> head = NULL;
    new_list -> length = 0;
}


bool appendList( ListPtr L, void *data ){
    NodePtr add_node = malloc(sizeof(NodePtr));
    NodePtr current_pointer = malloc(sizeof(NodePtr));
    add_node -> data = data;  // put data in
    add_node -> next = NULL; // make the next node NULL to end the list
    current_pointer = L -> head; 
    if (L -> head == NULL) {
        L -> head = add_node;
        return true;
    }
    else{
        while (current_pointer -> next != NULL) {
            current_pointer = current_pointer -> next;
        }
        current_pointer -> next = add_node;
    }
    return false;
}

// print value
void printList(ListPtr L ) {
    NodePtr current_pointer = malloc(sizeof(NodePtr)); 
    current_pointer = L -> head; 
    //printf("%d", current_pointer -> data);
    while (current_pointer -> next != NULL) {
        (*L -> dataPrinter)(current_pointer -> data);
        current_pointer = current_pointer -> next;
    }
    (*L -> dataPrinter)(current_pointer -> data);
}

// delete index
void *delElement( ListPtr L, int i ){
    NodePtr current_pointer = malloc(sizeof(NodePtr)); 
    current_pointer = L -> head; 
    NodePtr old_pointer = NULL;

    int counter = 0;
    while (current_pointer != NULL) {
        if (current_pointer -> data == i) {
            break;
        }
        old_pointer = current_pointer;
        current_pointer = current_pointer -> next;
    }
    if (current_pointer == NULL) {
        return NULL;
    }
    if (old_pointer == NULL) {
        L -> head = L -> head -> next;
    }
    else {
        old_pointer -> next = current_pointer -> next;
    }
    current_pointer -> next = NULL;
    //return current_pointer;
}

int length(ListPtr L ) {
    int counter = 1;
    NodePtr current_pointer = L -> head;

    while(current_pointer != NULL) {
        counter += 1;
        current_pointer = current_pointer -> next;
    }
    printf("%d", counter);
    return counter;
}

void *getElement( ListPtr L, int i) {
    //NodePtr add_data = malloc(sizeof(NodePtr));
    NodePtr current_pointer = malloc(sizeof(NodePtr));
    current_pointer = L -> head;

    int counter = 0;
    while (current_pointer != NULL) {
        if (counter == i) {
            return (current_pointer -> data);
        }
        counter += 1;
        current_pointer = current_pointer -> next;
    }

}

int findElement( ListPtr L, void *comp ) {
    NodePtr current_pointer = malloc(sizeof(NodePtr)); 
    current_pointer = L -> head;
    while (current_pointer != NULL) {
        if(current_pointer -> data == comp) {
            return current_pointer;
        }
        else {
            return -1;
        }
        current_pointer = current_pointer -> next;
    }
    return current_pointer;
}

bool insertElement(ListPtr L, int pos, void *data) {

}

// (*L -> dataPrinter)(current -> data)    current = NodeObj
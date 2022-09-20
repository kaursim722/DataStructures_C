#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"

/* TODO: implement get_min
returns minumum element in heap/shortest processing time
*/

int get_min(Heap* h) {                                  // functions used in this file are implemented from the CSE101 textbook, intro to algorithms 3rd edition
    if (h -> size <= 0) {
        return;
    }
    heapify(h, 1);                                      // sort heap
    return h -> id[1];
}

//------------------------------------------------------------------------

/* TODO: implement extract_min
extracts and returns min element in heap
note that heap property must be maintained after extraction
also check for valid input (cannot extract from empty heap)
*/

int extract_min(Heap* h) {                      
    if (h -> size <= 0) {                              //check whether the size of the heap is greater than 0
        return;
    }
    else {
        int min = h -> id[1];                           
        h -> array[1] = h -> array[h -> size];
        h -> id[1] = h -> id[h -> size];              // extract min
        h -> size = h -> size - 1;                    // decrease size of heap
        heapify(h, 1);
        return min;
    }
}


//------------------------------------------------------------------------

/* TODO: implement increase_priority
This function increases priority of element at index i to 'new_value'
*/

void increase_priority(Heap* h, int i, int new_value, int idn) {
    if (new_value > h -> array[i]) {
        return;
    }
    h -> array[i] = new_value;
    h -> id[i] = idn;
    while ((i > 1) && (h -> array[parent(i)] > h -> array[i])) {
        swap(h -> array, i, parent(i));
        swap(h -> id, i, parent(i));
        i = parent(i);
        heapify(h, 1);
    }
}


//------------------------------------------------------------------------

/* TODO: implement insert functionality
This function inserts priority 'value' into heap
You will need to have implemented the increase_priority and use it here
*/

void insert(Heap* h, int id, int value) {               
    h -> size = h -> size + 1;              
    h -> array[h -> size] = __INT_MAX__;            // array heap size = infinity  
    h -> id[h -> size] = __INT_MAX__;               // copy to id
    increase_priority(h, h -> size, value, id);     // call priority function
}

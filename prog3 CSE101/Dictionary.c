#include "List.h"
#include "HashTable.h"
#include "Dictionary.h"
#include <stdio.h>

typedef struct Dictionary {
int		slots;				// total number of slots in hash table
int		size;				// number of elements currently in dictionary
ListPtr  *hash_table;	    // hash_table is array of ListPtrs
} Dictionary;			// dictionary is maintained as a hash table.

//TODO: Implement a key comparison function to pass to list. (This only needs to check for equality)
//Hint: Look at List.h to see what kind of comparison function the list expects

int dataCompare(void *func_kv1, void *func_kv2) {           // function used to compare the two keys
    KVPair *kv1 = (KVPair*) func_kv1;
    KVPair *kv2 = (KVPair*) func_kv2;
    if (strcmp(kv1 -> key, kv2 -> key) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

//TODO: Implemement all functions from headers  

// function to create dictionaries with a specific size
Dictionary *dictionary_create(int hash_table_size, void (*dataPrinter)(void *data), void (*freeData)(KVPair *kvPair)) {
    Dictionary *d = (Dictionary *)malloc(sizeof(Dictionary));
    int i;
    d -> slots = hash_table_size;                                                                           // initialize slots with the size of the hash_table
    d -> size = 0;                                                                                          // the size starts at 0 and increments and decrements as the insert/delete function is called
    d -> hash_table = (ListPtr *)calloc(sizeof(ListPtr), hash_table_size);                                  // make hash_table with size of hash_table
    for (i = 0; i < d -> slots; i++) {                                                                      // for loop through the slots
        d -> hash_table[i] = list_create(dataCompare, dataPrinter, (void(*)(void*))freeData);               // create list at that hash index 
        list_print(d -> hash_table[i]);
    }
    return d;                                                                                               // return dictionary
}

void dictionary_destroy(Dictionary *d, bool freeData) {
    for (int i = 0; i < d -> slots; i++) {                                                                   // for loop through the slots
        list_destroy(d -> hash_table[i], freeData);                                                          // destroy the list at the specified index
    }
    free(d -> hash_table);
    free(d);
}

bool dictionary_insert(Dictionary *D, KVPair *elem) {
    int hash_index = ht_hash(elem -> key, D -> slots);                                                        // hash index for given key 
    KVPair *pair1 = (KVPair *)malloc(sizeof(KVPair));                   
    if (dictionary_find(D, elem -> key) == NULL) {                                                            // if the key is not in the dictionary
        list_append(D -> hash_table[hash_index], elem);                                                       // append the element at the index hashed and increase size of dictionary
        D -> size++;
        return true;
    }
    else {
        pair1 = list_get_index(D -> hash_table[hash_index], list_find_element(D -> hash_table[hash_index], elem));          // if != NULL then increase the value and the size of dictionary
        pair1 -> value++;
        D -> size++;
        return false;
    }  
}


KVPair *dictionary_delete(Dictionary *D, char *key) {                                       
    KVPair *pair1 = (KVPair *)malloc(sizeof(KVPair));                                   //malloc KV pairs
    KVPair *pair2 = (KVPair *)malloc(sizeof(KVPair));
    pair2 -> key = key; 
    pair2 -> value = 5; 
    if (dictionary_find(D, key) == NULL) {                      
        return NULL;
    }
    else {
        int hash_index = ht_hash(key, D -> slots);                                      // if the key is already in the dictionary, hash an index 
        int find_index = list_find_element(D -> hash_table[hash_index], pair2);         // find/get the element and store the int into a variable
        pair1 = list_get_index(D -> hash_table[hash_index], find_index);                
        list_del_index(D -> hash_table[hash_index], find_index);                        // delete the index and decrease the size of dictionary
        D -> size--;
        return pair1;                                                                   // return KV Pair
    }

}

KVPair *dictionary_find(Dictionary *D, char *k){                                        // function used to find a specific entry from a dictionary at a given key
    KVPair *pair1 = (KVPair *)malloc(sizeof(KVPair));                                   
    pair1 -> key = k;
    pair1 -> value = 2;
    KVPair *pair2 = (KVPair *)malloc(sizeof(KVPair));           
    int hash_index = ht_hash(k, D -> slots);                                            // hash an index
    if (list_find_element(D -> hash_table[hash_index], pair1) == -1)  {                 
        return NULL;
    }
    else {
        int find_index = list_find_element(D -> hash_table[hash_index], pair1);         // if the element is in the list, find the index
        pair2 = list_get_index(D -> hash_table[hash_index], find_index);                // store index in KVPair
        return pair2;                                                                   // return KVPair
    } 
} 

void dictionary_print(Dictionary *D) {                                                  // print the formatted Dictionary using for loop
    for (int i=0; i < D -> slots; i++) {
        if (D -> hash_table[i] != NULL) {
            list_print(D -> hash_table[i]);
        }
    }
}

int dictionary_size(Dictionary *D) {
    return D -> size;                                                                      // return final size of dictionary
}
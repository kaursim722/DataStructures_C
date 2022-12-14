#include "HashTable.h"

unsigned long ht_string2int(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

//TODO: Implement
unsigned int ht_hash(char *key, unsigned int slots) {
    // TODO: Implement
    /* unsigned long smth = ht_string2int(key);
    printf("%s",smth);
    unsigned int smth2 = smth % slots;
    printf("%s",smth2);
    return smth2; */
    //printf("%d", slots);
    return ht_string2int(key) % slots;
    //return ht_string2int(key) % slots;
}
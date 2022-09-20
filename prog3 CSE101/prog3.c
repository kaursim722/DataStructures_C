// Implement the text process application
// The output function is provided to you.
#include "Dictionary.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

//This is used internally by the output function. You don't need to change this value
#define WORD_BUFFER_SIZE 50


/**
 * @brief Checks if a character is in the char array.
 * 
 * @param ch The character to check
 * @param charArr The ckaracter array to compare against
 * @return true ch is in charArr
 * @return false ch is not in charArr
 */
bool any_char(char ch, char *charArr) {
    while (*charArr != 0) {
        if (ch == *charArr++) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the distance to the closest delimeter.
 * 
 * @param word The string to look through
 * @param delim The delimeter(s) to search for
 * @return uint8_t The number of characters in the word 
 */
uint8_t word_length(char *str, char *delims) {
    int i = 0;
    while (!any_char(str[i], delims) && str[i] != 0) {
        i++;
    }
    return i;
}

/**
 * @brief Prints the output to stdout. Accepts one line of output at a time.
 * 
 * @param wordFreqs A dictionary of words to format according to their frequency
 * @param wordLengths A dictionary of words to format according to their length
 * @param text One output line to format
 */
void printOutput(Dictionary *wordFreqs, Dictionary *wordLengths, char *text) {
    char wordBuffer[WORD_BUFFER_SIZE] = {0};

    while (*text != 0) {
        uint8_t length = word_length(text, " \n");
        assert(length < WORD_BUFFER_SIZE - 1);
        memcpy(wordBuffer, text, length);
        text = text + length;
        wordBuffer[length] = 0;
        KVPair *freq = dictionary_find(wordFreqs, wordBuffer);
        KVPair *len = dictionary_find(wordLengths, wordBuffer);
        if (freq == NULL && len == NULL) {
            printf("%s ", wordBuffer);
        } else {
            printf("<span style=\"");
            if (freq != NULL) {
                uint8_t r = (*(int*)freq->value) * 23;
                uint8_t g = (*(int*)freq->value) * 29;
                uint8_t b = (*(int*)freq->value) * 31;  
                printf("color:#%02x%02x%02x;font-weight:bold;", r, g, b);
            }
            if (len != NULL) {
                printf("font-size:%dpx;", 2 * (*(int*)len->value));
            }
            printf("\">%s</span> ", wordBuffer);
        }

        if (*text != 0) { // If delimiter is not null byte, then skip over it. 
            text += 1;
        }
    }
    printf("<br/>\n");
}

void *dataPrinter(void *data) {
    KVPair *pair1 = (KVPair *)malloc(sizeof(KVPair));
    pair1 = data; 
    printf("%s : %d\n", pair1 -> key, pair1 -> value);
}

void *freeData() {

}


int main(void) {
    // TODO: Read in stopwords from stdin. Treat spaces as word delimiters.
   
    printf("main");

    char list_word[256];
    /* char* char_word = (char*)malloc(100);
    int i = 0;
    while(i != "====") {
        fgets(list_word, 30000, stdin);
        scanf("%s", list_word);
        printf("%s", list_word);
        break;
    }  */

    printf("%s", "stopwords while");

    // TODO: Read in words from stdin. Treat spaces as word delimiters.
 
    while(!feof(stdin)) {                        // while the file doesnt end
        scanf("%s", list_word); 
        //scanf("%s", char_word);               
        printf("%s ", list_word);
    }
    // TODO: Add each word to freq and length dictionary or update count, if not in stopwords
    printf("%s", "before creating");
    Dictionary* dict_freq = dictionary_create(100, dataPrinter, freeData);
    Dictionary* dict_len = dictionary_create(100, dataPrinter, freeData); 
    Dictionary* dict_stop = dictionary_create(100, dataPrinter, freeData);
    printf("before mallocing");
    KVPair *pair = (KVPair *)malloc(sizeof(KVPair));
    KVPair *pair2 = (KVPair *)malloc(sizeof(KVPair));
    KVPair *pair3 = (KVPair *)malloc(sizeof(KVPair));
    pair -> key = "people";
    pair -> value = 2;
    pair2 -> key = "horse";
    pair2 -> value = 4;

    printf("%s", pair -> key);
    printf("%d", pair -> value);
    dictionary_insert(dict_freq, pair);
    //dataPrinter(dict_freq);

    // TODO: Remove everything but top 25 freq words, and everything but top 20 len words



    // Hint: You can try keeping the same KV elements in both dictionary and list.
    //       Give the list a comparator function which takes into account both word frequency and alphabetic order of word.
    //       Sort list once all words have been processed by the dictionary
    //       Then you can remove the ones not needed form the dictionary before passing it in.



}
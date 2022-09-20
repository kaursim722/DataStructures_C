#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct EventObj{
    char *name;
    int time;
} EventObj;
typedef EventObj* EventPtr;


// provided for output header formatting
void print(ListPtr l, char *agenda_name) {
    printf("======== %s ========\n", agenda_name);
    printList(l);
    printf("===== END OF %s =====\n", agenda_name);
}


bool dataEqual(void *obj1, void*obj2) {
    EventPtr compare1 = (EventObj*) obj1;
    EventPtr compare2 = (EventObj*) obj2;
    if(compare1 -> name == compare2 -> name) {
        printf("hi\n");
        return true;
    }
    else {
        printf("bye\n");
        return false;
    }
}

void dataPrinter(void *data) {
    EventPtr time_frmt = (EventObj*) data;
    if ((time_frmt -> time) < 10) {
        printf("0%d:00 %s", (time_frmt -> time), (time_frmt-> name));
    }
    else {
        printf("%d:00 %s", (time_frmt -> time), (time_frmt-> name));
    }
}

void freeData(void *data) {

}


int main(int argc, char **argv) {
	// declare 2 lists
    ListPtr List1 = newList(&dataEqual, &dataPrinter, &freeData);
    ListPtr List2 = newList(&dataEqual, &dataPrinter, &freeData);

    // accept input from the user
    char list_command[100];
    char list_obj[100];
    char list_obj2[100];
    char list_event[100];
    char list_event2[100];
    int list_time;

    char list_swap[] = "SWAP";
    char list_add[] = "ADD";
    char list_del[] = "DEL";
    char list_merge[] = "MERGE";
    char list_print[] = "PRINT";
    
    FILE *in_file = fopen("test.txt", "r");
    while(!feof(stdin)) {
        scanf("%s", list_command);
        printf("%s", list_command);
        if(strcmp(list_command, list_add) == 0) {
            scanf("%s[^\"] %[^\n]", list_obj);
            printf("%s",list_obj);
            scanf("%s[^\"] %[^\n]", list_event);
            printf("%s", list_event);
            scanf("%d", list_time);
            printf("%s", list_time);
        }
        else if(strcmp(list_command, list_swap) == 0) {
            scanf("%s[^\"] %[^\n]", list_obj);
            printf("%s",list_obj);
            scanf("%s[^\"] %[^\n]", list_event);
            printf("%s", list_event);
            scanf("%s[^\"] %[^\n]", list_event2);
            printf("%s", list_event2);
        }
        else if(strcmp(list_command, list_del) == 0) {
            scanf("%s[^\"] %[^\n]", list_obj);
            printf("%s",list_obj);
            scanf("%s[^\"] %[^\n]", list_event);
            printf("%s", list_event);
        }
        else if(strcmp(list_command, list_merge) == 0) {
            scanf("%s[^\"] %[^\n]", list_obj);
            printf("%s",list_obj);
            scanf("%s[^\"] %[^\n]", list_obj2);
            printf("%s",list_obj2);
        }
        else if(strcmp(list_command, list_print) == 0) {
            scanf("%s[^\"] %[^\n]", list_obj);
            printf("%s",list_obj);
        }
    }


    EventObj* event1 = malloc(sizeof(EventObj));
    event1 -> name = "Study\n";
    event1 -> time = 8;
	EventObj* event2 = malloc(sizeof(EventObj));
    event2 -> name = "Drink water\n";
    event2 -> time = 12;
    EventObj* event3 = malloc(sizeof(EventObj));
    event3 -> name = "Take a walk\n";
    event3 -> time = 11;
    EventObj* event4 = malloc(sizeof(EventObj));
    event4 -> name = "Meeting with prof\n";
    event4 -> time = 4;
    EventObj* event5 = malloc(sizeof(EventObj));
    event5 -> name = "Swimming\n";
    event5 -> time = 5;
    
	
    appendList(List1, event1);
    appendList(List1, event2);
    appendList(List1, event3);
    appendList(List1, event4);
    appendList(List1, event5);
    //delElement(List1, 3);
    dataEqual(event1, event5);
    //length(List1);
    
    print(List1, "MyList");

    return 0;
	// process input and modify appropriate list
	



	// be sure to release memory
}
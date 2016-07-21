#ifndef Linklist_H
#define Linklist_H

#include <stdint.h>
#include "projectStruct.h"


struct ListElement{
   struct ListElement *next;
   struct ListElement *prev;
   uint32_t actionTime;
   void (*callBack)(void* unknown);
   void *args;
};

struct Linkedlist{
	  struct ListElement *head;
	  struct ListElement *tail;
    uint32_t curTime;
    uint32_t baseTime;
    int callBackState;
}; 

struct Linkedlist *createLinkedList();
struct ListElement *createLinkedElement(int x);
void addList( struct Linkedlist *newList, struct ListElement *newElement);


#endif // Linklist_H

#ifndef Linklist_H
#define Linklist_H

#include <stdint.h>
#include "projectStruct.h"

typedef struct ListElement_t ListElement;
struct ListElement_t{
   ListElement *next;
   ListElement *prev;
   void (*callBack)(void* unknown);
   void *args;
   uint16_t actionTime;
};
typedef struct Linkedlist_t Linkedlist;
struct Linkedlist_t{
	  ListElement *head;
	  ListElement *tail;
    uint32_t curTime;
    uint32_t baseTime;
    int callBackState;
    int count;
}; 

void elementDelete(ListElement* Node);
void linkedListRemove(Linkedlist *newList, ListElement *newElement);
Linkedlist *createLinkedList();
ListElement *createLinkedElement(int x);
void addList(  Linkedlist *newList, ListElement *newElement);

#endif // Linklist_H

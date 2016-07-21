//General Library
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//Own Library
#include "Linklist.h"
#include "projectStruct.h"

struct Linkedlist *createLinkedList(){
  struct Linkedlist *list_NULL = malloc(sizeof(struct Linkedlist));;
  list_NULL->tail = NULL;
  list_NULL->head = NULL;
  list_NULL->curTime = 0;
  list_NULL->baseTime = 0;
  return list_NULL;
}

struct ListElement *createLinkedElement(int x){
  struct ListElement *newptr = malloc(sizeof(struct ListElement));
  newptr->actionTime = x;
  newptr->next = NULL;
  newptr->prev = NULL;
  return newptr;
}
 
void addList(  struct Linkedlist *newList, struct ListElement *newElement){
	 if(newList->head == NULL)
	 {
      newList->head = newElement;
      newElement->prev = newList->head;
	 }
	 else 
	 {
		 for(newList->tail = newList->head; newList->tail->next!=NULL ; newList->tail = newList->tail->next );
     newList->tail->next = newElement;
     newElement->prev = newList->tail;
	 }
}

void addListInCycle(  struct Linkedlist *newList, struct ListElement *newElement){
	 if(newList->head == NULL)
	 {
      newList->head = newElement;
      newList->head->prev = newElement;  
      newElement->next = newList->head;
      newElement->prev = newList->head;
	 }
	 else 
	 {
     newList->head->prev->next = newElement; // the next of latest element point to the address of new Element.
     newElement->prev = newList->head->prev; // the latest element address is recorded by the previous of new element.
     newList->head->prev = newElement;       // the previous of head point to new Element to continue the cycle link-list.
     newElement->next = newList->head;       // the next of new element point to head address to continue the cycle link-list.
	 }
}


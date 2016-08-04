//General Library
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//Own Library
#include "Linklist.h"
#include "projectStruct.h"

Linkedlist *createLinkedList(){
  Linkedlist *newList = malloc(sizeof(Linkedlist));;
  newList->tail = NULL;
  newList->head = NULL;
  newList->curTime = 0;
  newList->baseTime = 0;
  newList->count = 0;
  return newList;
}

ListElement *createLinkedElement(int x){
  ListElement *newElem = malloc(sizeof(ListElement));
  newElem->actionTime = x;
  newElem->next = NULL;
  newElem->prev = NULL;
  return newElem;
}
 

void addList(  Linkedlist *newList, ListElement *newElement){
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
     newList->count++;
}

void elementDelete(ListElement* deleteNode){
   deleteNode->prev->next = deleteNode->next;
   deleteNode->next->prev = deleteNode->prev;
  // deleteNode->next = NULL;
   deleteNode->prev = NULL;
}

void linkedListRemove(Linkedlist *newList, ListElement *elem){
  
  if(elem->next != elem){
   if(newList->head != NULL && newList->head == elem){
     newList->head = newList->head->next;
   }
   elementDelete(elem);
  }else{
   newList->head->next = NULL;
   newList->head->prev = NULL;
   newList->head = NULL;
  }
  newList->count--;
}




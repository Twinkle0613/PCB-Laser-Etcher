#include "Linklist.h"
#include "malloc.h"
#include <stdlib.h>
#include <stdio.h>

struct Linkedlist *createLinkedList(){
	struct Linkedlist *list_NULL = malloc(sizeof(struct Linkedlist));;
 	list_NULL->tail = NULL;
  list_NULL->head = NULL;
  return list_NULL;
}

struct ListElement *createLinkedElement(int x){
	  struct ListElement *newptr = malloc(sizeof(struct ListElement));
	  newptr->actionTime = x;
	  newptr->next = NULL;
		return newptr;
}
 
void addList(  struct Linkedlist *newList, struct ListElement *newElement)
{
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


// void deleteListElement(struct Liskedlist *LinkList,int value){
  // struct ListElement* temp;
  // if(LinkList->head == NULL){
    
  // }else{
    
    
    
    
    
  // }
  
// }
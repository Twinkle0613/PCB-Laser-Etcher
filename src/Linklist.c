#include "Linklist.h"
#include "malloc.h"
#include <stdlib.h>
#include <stdio.h>

struct Linkedlist *createLinkedList(){
	struct Linkedlist *list_NULL = malloc(sizeof(struct Linkedlist));;
 	list_NULL->tail = NULL;
  list_NULL->Head = NULL;
  return list_NULL;
}

struct ListElement *createLinkedElement(int x){
	  struct ListElement *newptr = malloc(sizeof(struct ListElement));
	  newptr->value = x;
	  newptr->next = NULL;
		return newptr;
}
 
 
int addList( struct ListElement *newElement, struct Linkedlist *newList)
{
	 if(newList->Head == NULL)
	 {
		       newList->Head = newElement;
					 	printf("%d\n",newList->Head->value);
		       return newList->Head->value; 
		}
	 else 
	 {
		 for(newList->tail = newList->Head; newList->tail->next!=NULL ; newList->tail = newList->tail->next );
	            newList->tail = newElement;
							printf("%d\n",newList->tail->value);
							return newList->tail->value;
	 }
}
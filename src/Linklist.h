#ifndef Linklist_H
#define Linklist_H
#include <stdint.h>

struct ListElement
{
	  struct ListElement *next;
    struct ListElement *achor;
		uint32_t actionTime;
};
 
struct Linkedlist
{
	 struct ListElement *head;
	 	struct ListElement *tail;
    
}; 

//typedef struct Linkedlist Linkedlist_t;
struct Linkedlist *createLinkedList();
struct ListElement *createLinkedElement(int x);
void addList( struct Linkedlist *newList, struct ListElement *newElement);


#endif // Linklist_H

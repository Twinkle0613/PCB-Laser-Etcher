#ifndef Linklist_H
#define Linklist_H
#include <stdint.h>
#include "projectStruct.h"


struct Linkedlist *createLinkedList();
struct ListElement *createLinkedElement(int x);
void addList( struct Linkedlist *newList, struct ListElement *newElement);


#endif // Linklist_H

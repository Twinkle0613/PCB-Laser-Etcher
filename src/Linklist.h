#ifndef Linklist_H
#define Linklist_H

struct ListElement
{
	  struct ListElement *next;
		int value;
};
 
 struct Linkedlist
{
	 struct ListElement *Head;
	 	struct ListElement *tail;
}; 



#endif // Linklist_H

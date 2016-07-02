#ifndef projectStruct_H
#define projectStruct_H
#include <stdint.h>


typedef struct motorInfo motorInfo_t;

struct ListElement
{
	  struct ListElement *next;
    struct ListElement *prev;
		uint32_t actionTime;
    void (*callBack)();
    void *motorID;
};


struct Linkedlist
{
	 struct ListElement *head;
	 	struct ListElement *tail;
    uint32_t curTime;
    uint32_t baseTime;
}; 

typedef struct{
  int state;
  struct ListElement timerElement;
  uint32_t period;
  uint8_t direation;         
  uint8_t step;     
  uint8_t sleep;
  uint8_t microstep;   
}motorInfo;   

#endif // projectStruct_H

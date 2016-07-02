#ifndef Coroutine_H
#define Coroutine_H
#include <stdint.h>
#include "Linklist.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"


#define startCoroutine() \
            switch( whichMotor->state ){   \
            case 0:
#define endCoroutine()          \
            }
            
#define yield()    whichMotor->state = __LINE__; \
                    return; \
                    case __LINE__:
                    
                    

 
void updateHead(struct Linkedlist *root);
void timerDelay(struct ListElement* timerElement,uint32_t period);
void coroutine(motorInfo* whichMotor);
            
#endif // Coroutine_H

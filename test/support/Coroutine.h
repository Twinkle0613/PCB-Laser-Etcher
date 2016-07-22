#ifndef Coroutine_H
#define Coroutine_H

//General Library
#include <stdint.h>
//STM standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"
//Own Library
#include "DMA.h"
#include "DMA_setting.h"
#include "Timer.h"
#include "Linklist.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "RelativeTimeLinkList.h"


#define startCoroutine() \
            switch( whichMotor->state ){   \
            case 0:
#define endCoroutine()          \
            }
            
#define yield()    whichMotor->state = __LINE__; \
                    return; \
                    case __LINE__:
                    
                    

// void _timerDelay(struct ListElement* timerElement,uint32_t period);
// void motorControl(motorInfo* whichMotor);
// void headPointToNext(struct Linkedlist *root);

#endif // Coroutine_H

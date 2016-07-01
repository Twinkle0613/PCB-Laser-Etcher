#ifndef Coroutine_H
#define Coroutine_H
#include <stdint.h>
#include "Linklist.h"

#define startCoroutine() \
            switch( whichMotor->state ){   \
            case 0:
#define endCoroutine()          \
            }
            
#define yield()    whichMotor->state = __LINE__; \
                    return; \
                    case __LINE__:
                    
                    
typedef struct{
  int state;
  int i;
}CoroutineInfo;


 

motorInfo* motorInit(void);

            
#endif // Coroutine_H

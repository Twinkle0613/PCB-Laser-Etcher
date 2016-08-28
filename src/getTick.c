#include "getTick.h"


uint32_t getTick(TIM_TypeDef* TIMx){
   return ( (TIMx->CNT&0x0000FFFF) );
}
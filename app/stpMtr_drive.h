#ifndef __stpMtr_drive__
#define __stpMtr_drive__
#include <stdint.h>
#include "stm32f10x_spi.h"#include "stm32f10x_gpio.h"

typedef struct
{
  uint8_t Direation;         
  uint8_t Step;     
  uint8_t Sleep;
  uint8_t Reset;   
  uint8_t Microstep;   
  uint8_t State;         
}StpMtr_InitTypeDef;

/** @defgroup StpMtr_Notation_direction 
  * @{
  */
#define StpMtr_Clockwise        ((uint8_t)0x80)
#define StpMtr_Anti_clockwise   ((uint8_t)0x00)

/** @defgroup StpMtr_State
  * @{
  */
#define StpMtr_High   ((uint8_t)0x40)
#define StpMtr_Low    ((uint8_t)0x00)

/** @defgroup StpMtr_Sleep_Mode
  * @{
  */
#define StpMtr_Slp_On  ((uint8_t)0x00)
#define StpMtr_Slp_Off ((uint8_t)0x20)

/** @defgroup StpMtr_Reset
  * @{
  */
#define StpMtr_Rst_On  ((uint8_t)0x00)
#define StpMtr_Rst_Off ((uint8_t)0x10)

/** @defgroup StpMtr_Mircostep
  * @{
  */
#define StpMtr_Full_step       ((uint8_t)0x00) // 2 phase
#define StpMtr_Half_step       ((uint8_t)0x08) // 1/2 phase
#define StpMtr_Quater_step     ((uint8_t)0x04)// 1/4 phase
#define StpMtr_Eighth_step     ((uint8_t)0x0C)// 1/8 phase
#define StpMtr_Sixteenth_step  ((uint8_t)0x0E)// 1/16 phase

/** @defgroup StpMtr_Enable
  * @{
  */
#define StpMtr_Enable  ((uint8_t)0x00)
#define StpMtr_Disable ((uint8_t)0x01)


uint8_t stdMtr_drive_conf(uint8_t dir, uint8_t slp_mode,uint8_t microstep);
void sendConfToShiftReg(SPI_TypeDef* SPIx,uint16_t driver_conf);
void outputData();



#endif //__stpMtr_drive__
#ifndef Config_H
#define Config_H



#define Motor_Number 3
// DMA configuration
#define DMA_Channel DMA1_Channel3
#define RCC_AHBPeriph_DMA RCC_AHBPeriph_DMA1
#define DMA_Channel_IRQn DMA1_Channel3_IRQn
// TIM configuration
#define TIM TIM2
#define RCC_APBPeriph_TIM RCC_APB1Periph_TIM2
#define TIM_IRQn TIM2_IRQn
// SPI configuration
#define SPI SPI1
#define RCC_APBPeriph_SPI RCC_APB2Periph_SPI1

// GPIO configuration
#define GPIO GPIOA
#define RCC_APB2Periph_GPIO RCC_APB2Periph_GPIOA
#define NSS_PIN  GPIO_Pin_4
#define SCLK_PIN GPIO_Pin_5
#define MISO_PIN GPIO_Pin_6
#define MOSI_PIN GPIO_Pin_7

#endif // Config_H

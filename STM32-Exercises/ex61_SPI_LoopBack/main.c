#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "spi.h"

void Delay( uint32_t nTime );

// Initialize chip select PC03
void csInit(){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOC,GPIO_Pin_3, 1);
}

uint8_t txbuf [4], rxbuf [4];
uint16_t txbuf16 [4], rxbuf16 [4];

void main (){
  int i, j;
  csInit (); // Initialize chip select PC03
  spiInit (SPI2);

  for (i = 0; i < 8; i++){

    for (j = 0; j < 4; j++)
      txbuf [j] = i*4 + j;

    GPIO_WriteBit (GPIOC , GPIO_Pin_3 , 0); //SS start
    spiReadWrite (SPI2 , rxbuf , txbuf , 4, SPI_SLOW );
    GPIO_WriteBit (GPIOC , GPIO_Pin_3 , 1); //SS stop

    for (j = 0; j < 4; j++)
      if (rxbuf [j] != txbuf [j])
        assert_failed (__FILE__ , __LINE__ );
  }

  for (i = 0; i < 8; i++){

    for (j = 0; j < 4; j++)
      txbuf16 [j] = i*4 + j + (i << 8);

    GPIO_WriteBit (GPIOC , GPIO_Pin_3 , 0); //SS start
    spiReadWrite16 (SPI2 , rxbuf16 , txbuf16 , 4, SPI_SLOW );
    GPIO_WriteBit (GPIOC , GPIO_Pin_3 , 1); //SS stop

    for (j = 0; j < 4; j++)
      if ( rxbuf16 [j] != txbuf16 [j])
        assert_failed (__FILE__ , __LINE__ );
  }
}

// Timer code
static __IO uint32_t TimingDelay ;
void Delay( uint32_t nTime ){
  TimingDelay = nTime ;
  while ( TimingDelay != 0);
}

void SysTick_Handler (void){
  if ( TimingDelay != 0x00)
  TimingDelay --;
}

#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line){
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

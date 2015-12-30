#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "uart.h"

void Delay( uint32_t nTime );

int main(void){
  // Configure SysTick Timer

  if ( SysTick_Config ( SystemCoreClock / 1000) )
    while (1);

  uart_open(USART1,9600,0);

  char hello[13] = "Hello World!\n";
  while (1) {
    for( int i = 0 ; i<13 ; i++)
      uart_putc(hello[i],USART1);
    Delay (250);
    // wait 250 ms
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

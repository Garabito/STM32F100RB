#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "ST7735.h"

void Delay( uint32_t nTime );
void fillScreen(uint16_t color);

int main(void)
{
  ST7735_init();

  ST7735_backLight(1);

  while(1){

    fillScreen(RED);
    Delay(1000);
    fillScreen(GREEN);
    Delay(1000);
    fillScreen(BLUE);
    Delay(1000);

  }
  return 0;
}

void fillScreen(uint16_t color){
  uint8_t x,y;
  ST7735_setAddrWindow(0, 0, ST7735_width-1, ST7735_height-1, MADCTLGRAPHICS);
  for(x=0; x<ST7735_width; x++){
    for(y=0; y<ST7735_height; y++){
      ST7735_pushColor(&color, 1);
    }
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

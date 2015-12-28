# include <stm32f10x.h>

main (){
  int button;  
   
  //Pag 89 RM0041 Reference manual STM32F100xx
  //Enable clock
  RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN); //0x00000010 | 0x00000004 ( line 2045 stm32f10x.h )

  //Pag 110 RM0041 Reference manual STM32F100xx
  //configure button
  GPIOA->CRL |= GPIO_CRL_CNF0_0; //0x00000004 (line 2345 stm32f10x.h  Floating input )

  //configure led
  GPIOC->CRH |= GPIO_CRH_MODE8_1;//0x00000002 (line 2381 stm32f10x.h Output mode, max speed 2 MHz )

  while (1){
    button = ((GPIOA->IDR & GPIO_IDR_IDR0) == 1 );// ( (XXXX XXXX XXX? XXXX) & (0000 0000 0001 0000) line 2446 stm32f10x.h)

    if (button)
      GPIOC->BSRR = GPIO_BSRR_BS8; // 0x00000100 (line 2490 stm32f10x.h )
    else
      GPIOC->BSRR = GPIO_BSRR_BR8; // 0x01000000 (line 2507 stm32f10x.h )
  }

}


#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line){
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

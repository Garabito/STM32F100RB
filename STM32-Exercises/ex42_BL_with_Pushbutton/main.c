# include <stm32f10x.h>
# include <stm32f10x_rcc.h>
# include <stm32f10x_gpio.h>

void Delay( uint32_t nTime );

int main(void){
  GPIO_InitTypeDef
  GPIO_InitStructure ;

  // Enable Peripheral Clocks
  RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC , ENABLE );
  RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA , ENABLE );

  // Configure Pins
  GPIO_StructInit (&GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init (GPIOC , &GPIO_InitStructure );

  GPIO_StructInit (&GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init (GPIOA , &GPIO_InitStructure );

  // Configure SysTick Timer
  if ( SysTick_Config ( SystemCoreClock / 1000) )
    while (1);

  while (1) {
    static int ledval = 0;
    static int button = 0;
    button = GPIO_ReadInputDataBit (GPIOA , GPIO_Pin_0 );
    // toggle led
    GPIO_WriteBit (GPIOC , GPIO_Pin_9 , ( ledval ) ? Bit_SET : Bit_RESET );
    GPIO_WriteBit (GPIOC , GPIO_Pin_8 , ( button ) ? Bit_SET : Bit_RESET );
    ledval = 1 - ledval;

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

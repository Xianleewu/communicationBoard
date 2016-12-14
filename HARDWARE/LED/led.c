#include "led.h"

void LED_Init(void)
{
 
#ifdef ATK_V33
	RCC->APB2ENR|=1<<2;    //??PORTA??	   	 
	RCC->APB2ENR|=1<<5;    //??PORTD??	
	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 ????   	 
    GPIOA->ODR|=1<<8;      //PA8 ???
											  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2????
	GPIOD->ODR|=1<<2;      //PD.2??? 
	
#else
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	GPIO_SetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_12);
	
#endif	
	
	
}
 

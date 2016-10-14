#include "led.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //??PA,PD????
	
 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11| GPIO_Pin_12;				 //LED0-->PA.8 ????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //?????????GPIOA.8
 GPIO_SetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_12);	 //PA.8 ???
	
}
 

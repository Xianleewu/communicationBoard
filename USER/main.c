#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "text.h"	
#include "timer.h"

 
int main(void)
{  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置中断优先级分组2 
	delay_init();	    	 							//延时函数初始化	  
	uart_init(115200);	 								//串口初始化为9600			 
	LED_Init();         								//LED初始化	 													      													    
	//usmart_dev.init(72);								//usmart初始化	
 	mem_init();											//初始化内存池	    
	
	while(1)
	{
		delay_ms(500);
		LED0 = !LED0;
		printf("LED status:\r\n");
	}
	
}

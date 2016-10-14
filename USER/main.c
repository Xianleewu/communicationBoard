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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����2 
	delay_init();	    	 							//��ʱ������ʼ��	  
	uart_init(115200);	 								//���ڳ�ʼ��Ϊ9600			 
	LED_Init();         								//LED��ʼ��	 													      													    
	//usmart_dev.init(72);								//usmart��ʼ��	
 	mem_init();											//��ʼ���ڴ��	    
	
	while(1)
	{
		delay_ms(500);
		LED0 = !LED0;
		printf("LED status:\r\n");
	}
	
}

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
#include "wifi_config.h"
#include "wifi_function.h"

 
int main(void)
{  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����2 
	delay_init();	    	 							//��ʱ������ʼ��	  
	uart_init(115200);	 								//���ڳ�ʼ��115200
	USART2_Config();
	LED_Init();         								//LED��ʼ��	 													      													    
 	mem_init();											//��ʼ���ڴ��	    
	
	LED_Init();
	JLX12864G_086_GPIOInit();
	initial_lcd();
	clear_screen();
	delay_ms(200);
	display_GB2312_string(1,1,"WIFI RFID Zigbee");
	
	display_GB2312_string(3,1,"WIFI testing....");
	
	//ESP8266_Rst();
	
	ESP8266_AT_Test();
	printf("ESP8266 init finished !\r\n");
	ESP8266_BuildAP ("VideoStream","34567890", "3");
	
	while(1)
	{
		delay_ms(500);
		LED0 = !LED0;
		USART_printf(USART1,"this string out from uart1 \r\n");
		//USART_printf(USART2,"this string out from uart2 \r\n");
	}
	
}

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置中断优先级分组2 
	delay_init();	    	 							//延时函数初始化	  
	uart_init(115200);	 								//串口初始化115200
	USART2_Config();
	LED_Init();         								//LED初始化	 													      													    
 	mem_init();											//初始化内存池	    
	
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

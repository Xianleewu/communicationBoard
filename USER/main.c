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
#include "string.h"
#include "wifi_config.h"
#include "wifi_function.h"

 
int main(void)
{  
	char *recStr = NULL;
	ENUM_NetPro_TypeDef tcpConn = enumTCP;
	delay_init();	    	 							//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置中断优先级分组2 
	uart_init(115200);	 								//串口初始化115200
	USART2_Config();
	LED_Init();         								//LED初始化	 													      													    
 	mem_init();											//初始化内存池	    

#ifndef ATK_V33	
	JLX12864G_086_GPIOInit();
	initial_lcd();
	clear_screen();
	delay_ms(200);
	
	display_GB2312_string(1, 1, "WIFI RFID Zigbee");
	display_GB2312_string(3, 1, "WIFI testing....");
	display_GB2312_string(5, 1, "WIFI testing ok.");
	
#endif

	ESP8266_AT_Test();
	ESP8266_BuildAP ("smartAP","34567890", "3");

	PC_Usart("All init finished \n");
	
	ESP8266_Enable_MultipleId(ENABLE);
	
	ESP8266_StartOrShutServer ( ENABLE, "8080", "1000000");
	
	while(!ESP8266_Link_Server(tcpConn, "192.168.4.2", "8080", Multiple_ID_0))
	{
		
	}
	
	while(1)
	{
		LED1 = !LED1;
		ESP8266_SendString ( DISABLE, "hello from esp8266", sizeof("hello from esp8266"),  Multiple_ID_0);
		delay_ms(1000);
		recStr = ESP8266_ReceiveString ( DISABLE);
		ESP8266_SendString ( DISABLE, recStr, strlen(recStr),  Multiple_ID_0);
		delay_ms(1000);
	}
	
}

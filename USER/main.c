#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"

//ALIENTEK miniSTM32开发板实验1
//跑马灯实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	LCD_GPIOInit();
	delay_ms(200);
	initial_lcd();
	delay_ms(300);
	clear_screen();
	while(1)
	{
		display_graphic_16x16( 0, 0, "hello");
		LED0=0;
		LED1=1;
		delay_ms(300);	 //延时300ms
		LED0=1;
		LED1=0;
		delay_ms(300);	//延时300ms
	}
 }


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"

//ALIENTEK miniSTM32������ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
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
		delay_ms(300);	 //��ʱ300ms
		LED0=1;
		LED1=0;
		delay_ms(300);	//��ʱ300ms
	}
 }


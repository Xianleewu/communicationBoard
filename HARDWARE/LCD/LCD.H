#ifndef __LCD_H
#define __LCD_H	 
#include "sys.h"

typedef  unsigned char uchar;
typedef  unsigned int  uint;
typedef  unsigned long ulong; 
typedef	 signed int	   INT16S;

#define OL_SCLK PBout(3)	// 
#define OL_SDA  PBout(1)	// 
#define OL_RS   PBout(0)
#define OL_CS   PCout(5)
#define ROM_CS  PCout(4)
#define ROM_SCK PBout(4)
#define ROM_OUT PBout(5)
#define ROM_IN  PBout(6)

void LCD_GPIOInit(void);     //��ʼ��GPIO
//void delay(int n_ms);    
//void delay_us(int n_us);   
void initial_lcd(void);  //��ʼ��
void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void lcd_address(uint page,uint column);
void clear_screen(void);            //ȫ������
void display_128x64(uchar *dp);     //��ʾ128x64����ͼ��
void display_graphic_16x16(uchar page,uchar column,uchar *dp); //��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��
void display_graphic_8x16(uchar page,uchar column,uchar *dp);  //��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��
void display_graphic_5x8(uchar page,uchar column,uchar *dp);   //��ʾ5X8����ͼ��ASCII, ��5x8����������ַ�������ͼ��
void send_command_to_ROM( uchar datu );                        //��ָ�����Ѷ�ֿ�IC
static uchar get_data_from_ROM(void);                             //�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column); //��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column);  //��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column) ;  //��ָ����ַ��������д��Һ����ָ����page,column)������
void display_GB2312_string(uchar page,uchar column,uchar *text);  //�ڵ�pageҳ����column�У���ʾһ��16x16�����ֻ�8x16��ASCII��
void display_string_5x8(uchar page,uchar column,uchar *text);     //�ڵ�pageҳ����column�У���ʾһ��5x8�����ASCII��

		 				    
#endif
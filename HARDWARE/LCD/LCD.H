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

void LCD_GPIOInit(void);     //初始化GPIO
//void delay(int n_ms);    
//void delay_us(int n_us);   
void initial_lcd(void);  //初始化
void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void lcd_address(uint page,uint column);
void clear_screen(void);            //全屏清屏
void display_128x64(uchar *dp);     //显示128x64点阵图像
void display_graphic_16x16(uchar page,uchar column,uchar *dp); //显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标
void display_graphic_8x16(uchar page,uchar column,uchar *dp);  //显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标
void display_graphic_5x8(uchar page,uchar column,uchar *dp);   //显示5X8点阵图像、ASCII, 或5x8点阵的自造字符、其他图标
void send_command_to_ROM( uchar datu );                        //送指令到晶联讯字库IC
static uchar get_data_from_ROM(void);                             //从晶联讯字库IC中取汉字或字符数据（1个字节）
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column);  //从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column) ;  //从指定地址读出数据写到液晶屏指定（page,column)座标中
void display_GB2312_string(uchar page,uchar column,uchar *text);  //在第page页，第column列，显示一串16x16点阵汉字或8x16的ASCII字
void display_string_5x8(uchar page,uchar column,uchar *text);     //在第page页，第column列，显示一串5x8点阵的ASCII字

		 				    
#endif
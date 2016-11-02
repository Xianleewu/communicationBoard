#ifndef _LCD_H
#define _LCD_H

#include "stm32f10x.h"
#include "delay.h"

#define lcd_cs1_h GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define lcd_cs1_l GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define lcd_reset_h GPIO_SetBits(GPIOF,GPIO_Pin_1)
#define lcd_reset_l GPIO_ResetBits(GPIOF,GPIO_Pin_1)
#define lcd_rs_h GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define lcd_rs_l GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define lcd_sid_h GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define lcd_sid_l GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define lcd_sclk_h GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define lcd_sclk_l GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define Rom_CS_h GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define Rom_CS_l GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define Rom_SCK_h GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define Rom_SCK_l GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define Rom_OUT_h GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define Rom_OUT_l GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define Rom_IN_h GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define Rom_IN_l GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define Rom_OUT GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


void JLX12864G_086_GPIOInit(void);
void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void initial_lcd(void);
void lcd_address(uint page,uint column);
void clear_screen(void);
void display_128x64(uchar *dp);
void display_graphic_16x16(uchar page,uchar column,uchar *dp);
void display_graphic_8x16(uchar page,uchar column,uchar *dp);
void display_graphic_5x8(uchar page,uchar column,uchar *dp);
void send_command_to_ROM( uchar datu );
static uchar get_data_from_ROM(void);
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column);
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column);
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column);
void display_GB2312_string(uchar page,uchar column,uchar *text);
void display_string_5x8(uchar page,uchar column,uchar *text);



#endif

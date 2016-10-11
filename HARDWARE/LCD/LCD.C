#include "LCD.H"
#include "delay.h"
#include "sys.h"
#include "misc.h"

void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化
	GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 );		     //PA.8 输出高
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5 ;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化
	GPIO_SetBits(GPIOC,GPIO_Pin_4 | GPIO_Pin_5);		     //PA.8 输出高
}

//写指令到LCD模块
void transfer_command_lcd(int data1)   
{
	char i;
	OL_CS=0;
	OL_RS=0;
	for(i=0;i<8;i++)
   {
		OL_SCLK=0; 
		//delay_us(10);	 //加少量延时
		if(data1&0x80) OL_SDA=1;
		else OL_SDA=0;
		OL_SCLK=1;
		//delay_us(10);	 //加少量延时
	 	data1=data1<<=1;
   }
	OL_CS=1;
}

//写数据到LCD模块
void transfer_data_lcd(int data1)
{
	char i;
	OL_CS=0;
	OL_RS=1;
	for(i=0;i<8;i++)
	{
		OL_SCLK=0;
		if(data1&0x80) OL_SDA=1;
		else OL_SDA=0;
		OL_SCLK=1;
		data1=data1<<=1;
	}
	OL_CS=1;
}

//LCD模块初始化
void initial_lcd()
{
	//lcd_reset=0;        		//低电平复位
	delay_ms(100);
	//lcd_reset=1;		    	//复位完毕
	delay_ms(100);        
	transfer_command_lcd(0xe2);	 //软复位
	delay_ms(5);
	transfer_command_lcd(0x2c);  //升压步聚1
	delay_ms(50);	
	transfer_command_lcd(0x2e);  //升压步聚2
	delay_ms(50);
	transfer_command_lcd(0x2f);  //升压步聚3
	delay_ms(5);
	transfer_command_lcd(0x23);  //粗调对比度，可设置范围0x20～0x27
	transfer_command_lcd(0x81);  //微调对比度
	transfer_command_lcd(0x28);  //微调对比度的值，可设置范围0x00～0x3f
	transfer_command_lcd(0xa2);  //1/9偏压比（bias）
	transfer_command_lcd(0xc8);  //行扫描顺序：从上到下
	transfer_command_lcd(0xa0);  //列扫描顺序：从左到右
	transfer_command_lcd(0x40);  //起始行：第一行开始
	transfer_command_lcd(0xaf);  //开显示
}

void lcd_address(uint page,uint column)
{
	column=column-0x01;
	transfer_command_lcd(0xb0+page-1);   //设置页地址，每8行为一页，全屏共64行，被分成8页
	transfer_command_lcd(0x10+(column>>4&0x0f));	//设置列地址的高4位
	transfer_command_lcd(column&0x0f);	//设置列地址的低4位	
}

//全屏清屏
void clear_screen()
{
	unsigned char i,j;
	
		
	for(i=0;i<9;i++)
	{
		transfer_command_lcd(0xb0+i);
		transfer_command_lcd(0x10);
		transfer_command_lcd(0x00);
		for(j=0;j<132;j++)
		{
		  	transfer_data_lcd(0x00);
		}
	}
}

//显示128x64点阵图像
void display_128x64(uchar *dp)
{
	uint i,j;
	
	for(j=0;j<8;j++)
	{
		lcd_address(j+1,1);
		for (i=0;i<128;i++)
		{	
			transfer_data_lcd(*dp);					//写数据到LCD,每写完一个8位的数据后列地址自动加1
			dp++;
		}
	}
}


//显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标
void display_graphic_16x16(uchar page,uchar column,uchar *dp)
{
	uint i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{	
			transfer_data_lcd(*dp);					//写数据到LCD,每写完一个8位的数据后列地址自动加1
			dp++;
		}
	}
}

//显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标
void display_graphic_8x16(uchar page,uchar column,uchar *dp)
{
	uint i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<8;i++)
		{	
			transfer_data_lcd(*dp);					//写数据到LCD,每写完一个8位的数据后列地址自动加1
			dp++;
		}
	}
}


//显示5X8点阵图像、ASCII, 或5x8点阵的自造字符、其他图标
void display_graphic_5x8(uchar page,uchar column,uchar *dp)
{
	uint i;
	lcd_address(page,column);
	for (i=0;i<6;i++)
	{	
		transfer_data_lcd(*dp);
		dp++;
	}
	
}

//送指令到晶联讯字库IC
void send_command_to_ROM( uchar datu )
{
	uchar i;
	for(i=0;i<8;i++ )
	{
		ROM_SCK=0;
		delay_us(10);
		if(datu&0x80)ROM_IN = 1;
		else ROM_IN = 0;
		datu = datu<<1;
		ROM_SCK=1;
		delay_us(10);
	}
}

//从晶联讯字库IC中取汉字或字符数据（1个字节）
static uchar get_data_from_ROM(void)
{
	uchar i;
	uchar ret_data=0;
	for(i=0;i<8;i++)
	{
		ROM_OUT=1;
		ROM_SCK=0;
		//delay_us(1);
		ret_data=ret_data<<1;
		if( ROM_OUT )
			ret_data=ret_data+1;
		else
			ret_data=ret_data+0;
		ROM_SCK=1;
		//delay_us(1);
	}
	return(ret_data);
}


//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
	uchar i,j,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<16; i++ )
	    {
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	ROM_CS=1;
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
	uchar i,j,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<8; i++ )
	    {
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	ROM_CS=1;
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column) 
{
	uchar i,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	lcd_address(page,column);
	for(i=0; i<5; i++ )
	{
		disp_data=get_data_from_ROM();
		transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
	}
	ROM_CS=1;
}


//****************************************************************
ulong  fontaddr=0;
void display_GB2312_string(uchar page,uchar column,uchar *text)
{
	uchar i= 0;		
	void NVIC_SETPRIMASK(void);
	void NVIC_SETFAULTMASK(void);
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*32);

			get_and_write_16x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）15x16点的字符在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*32);
	
			get_and_write_16x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=16;
		}
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{									
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);			

			get_and_write_8x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=1;
			column+=8;
		}
		else
			i++;	
	}
	//NVIC_RESETPRIMASK();
	//NVIC_RESETFAULTMASK();
}

void display_string_5x8(uchar page,uchar column,uchar *text)
{
	unsigned char i= 0;
	void NVIC_SETPRIMASK(void);
	void NVIC_SETFAULTMASK(void);
	while((text[i]>0x00))
	{
		
		if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{						
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*8);
			fontaddr = (unsigned long)(fontaddr+0x3bfc0);			


			get_and_write_5x8(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中

			i+=1;
			column+=6;
		}
		else
		i++;	
	}
//	NVIC_RESETPRIMASK(void);
//	NVIC_RESETFAULTMASK(void);
}

#include "LCD.H"
#include "delay.h"
#include "sys.h"
#include "misc.h"

void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��
	GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 );		     //PA.8 �����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5 ;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��
	GPIO_SetBits(GPIOC,GPIO_Pin_4 | GPIO_Pin_5);		     //PA.8 �����
}

//дָ�LCDģ��
void transfer_command_lcd(int data1)   
{
	char i;
	OL_CS=0;
	OL_RS=0;
	for(i=0;i<8;i++)
   {
		OL_SCLK=0; 
		//delay_us(10);	 //��������ʱ
		if(data1&0x80) OL_SDA=1;
		else OL_SDA=0;
		OL_SCLK=1;
		//delay_us(10);	 //��������ʱ
	 	data1=data1<<=1;
   }
	OL_CS=1;
}

//д���ݵ�LCDģ��
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

//LCDģ���ʼ��
void initial_lcd()
{
	//lcd_reset=0;        		//�͵�ƽ��λ
	delay_ms(100);
	//lcd_reset=1;		    	//��λ���
	delay_ms(100);        
	transfer_command_lcd(0xe2);	 //����λ
	delay_ms(5);
	transfer_command_lcd(0x2c);  //��ѹ����1
	delay_ms(50);	
	transfer_command_lcd(0x2e);  //��ѹ����2
	delay_ms(50);
	transfer_command_lcd(0x2f);  //��ѹ����3
	delay_ms(5);
	transfer_command_lcd(0x23);  //�ֵ��Աȶȣ������÷�Χ0x20��0x27
	transfer_command_lcd(0x81);  //΢���Աȶ�
	transfer_command_lcd(0x28);  //΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f
	transfer_command_lcd(0xa2);  //1/9ƫѹ�ȣ�bias��
	transfer_command_lcd(0xc8);  //��ɨ��˳�򣺴��ϵ���
	transfer_command_lcd(0xa0);  //��ɨ��˳�򣺴�����
	transfer_command_lcd(0x40);  //��ʼ�У���һ�п�ʼ
	transfer_command_lcd(0xaf);  //����ʾ
}

void lcd_address(uint page,uint column)
{
	column=column-0x01;
	transfer_command_lcd(0xb0+page-1);   //����ҳ��ַ��ÿ8��Ϊһҳ��ȫ����64�У����ֳ�8ҳ
	transfer_command_lcd(0x10+(column>>4&0x0f));	//�����е�ַ�ĸ�4λ
	transfer_command_lcd(column&0x0f);	//�����е�ַ�ĵ�4λ	
}

//ȫ������
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

//��ʾ128x64����ͼ��
void display_128x64(uchar *dp)
{
	uint i,j;
	
	for(j=0;j<8;j++)
	{
		lcd_address(j+1,1);
		for (i=0;i<128;i++)
		{	
			transfer_data_lcd(*dp);					//д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
		}
	}
}


//��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��
void display_graphic_16x16(uchar page,uchar column,uchar *dp)
{
	uint i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{	
			transfer_data_lcd(*dp);					//д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
		}
	}
}

//��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��
void display_graphic_8x16(uchar page,uchar column,uchar *dp)
{
	uint i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<8;i++)
		{	
			transfer_data_lcd(*dp);					//д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
		}
	}
}


//��ʾ5X8����ͼ��ASCII, ��5x8����������ַ�������ͼ��
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

//��ָ�����Ѷ�ֿ�IC
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

//�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�
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


//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
	uchar i,j,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //��ַ�ĸ�8λ,��24λ
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //��ַ����8λ,��24λ
	send_command_to_ROM(fontaddr&0xff);				 //��ַ�ĵ�8λ,��24λ
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<16; i++ )
	    {
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//д���ݵ�LCD,ÿд��1�ֽڵ����ݺ��е�ַ�Զ���1
		}
	}
	ROM_CS=1;
}

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
	uchar i,j,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //��ַ�ĸ�8λ,��24λ
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //��ַ����8λ,��24λ
	send_command_to_ROM(fontaddr&0xff);				 //��ַ�ĵ�8λ,��24λ
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<8; i++ )
	    {
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//д���ݵ�LCD,ÿд��1�ֽڵ����ݺ��е�ַ�Զ���1
		}
	}
	ROM_CS=1;
}

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column) 
{
	uchar i,disp_data;
	ROM_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //��ַ�ĸ�8λ,��24λ
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //��ַ����8λ,��24λ
	send_command_to_ROM(fontaddr&0xff);				 //��ַ�ĵ�8λ,��24λ
	lcd_address(page,column);
	for(i=0; i<5; i++ )
	{
		disp_data=get_data_from_ROM();
		transfer_data_lcd(disp_data);	//д���ݵ�LCD,ÿд��1�ֽڵ����ݺ��е�ַ�Զ���1
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
			//������壨GB2312�������ھ���Ѷ�ֿ�IC�еĵ�ַ�����¹�ʽ�����㣺
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//���ڵ���8λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*32);

			get_and_write_16x16(fontaddr,page,column);	 //��ָ����ַ��������д��Һ����ָ����page,column)������
			i+=2;
			column+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			//������壨GB2312��15x16����ַ��ھ���Ѷ�ֿ�IC�еĵ�ַ�����¹�ʽ�����㣺
			//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
			//���ڵ���8λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*32);
	
			get_and_write_16x16(fontaddr,page,column);	 //��ָ����ַ��������д��Һ����ָ����page,column)������
			i+=2;
			column+=16;
		}
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{									
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);			

			get_and_write_8x16(fontaddr,page,column);	 //��ָ����ַ��������д��Һ����ָ����page,column)������
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


			get_and_write_5x8(fontaddr,page,column);	 //��ָ����ַ��������д��Һ����ָ����page,column)������

			i+=1;
			column+=6;
		}
		else
		i++;	
	}
//	NVIC_RESETPRIMASK(void);
//	NVIC_RESETFAULTMASK(void);
}
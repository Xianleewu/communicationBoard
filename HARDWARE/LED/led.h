#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define ATK_V33

#ifdef ATK_V33

#define LED0 PAout(8)// PA8
#define LED1 PDout(2)// PD2

#else

#define LED0 PBout(11)	// PA8
#define LED1 PBout(12)	// PD2	

#endif

void LED_Init(void);//≥ı ºªØ

		 				    
#endif

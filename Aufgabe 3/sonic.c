#include "sonic.h"
#include "lcd.h"

void sonic_init()
{
	LPC_IOCON->P1_4 = 0x0;
	LPC_IOCON->P1_17 = 0x0;
	LPC_IOCON->P1_18 = 0x0;
	
}

void sonic_measure(uint8_t sensor){
	
	volatile uint8_t stat = 0;
	volatile uint16_t count = 0;
	
	LPC_GPIO1->DIR = 1 << 4;
	LPC_GPIO1->SET = 1 << 4;
	while(count < 500) {
		count++;
	}
	LPC_GPIO1->CLR = 1 << 4;
	
	LPC_GPIO1->DIR ^= 1 << 4;
	//LPC_GPIO1->PIN = 0;
	count = 0;
	while(!stat){
		stat = LPC_GPIO1->PIN & (1<<4);
	}
	
	while(stat){
		stat = LPC_GPIO1->PIN & (1<<4);
		count++;
	}
	
	point p = {.x = 0, .y = 0};
	count /= 100;
	if(count > 240){
		count = 240;		
	}
	draw_rectangle(&p, 5, count, 1);
	clr_rectangle(&p, 5, count, 1);
}

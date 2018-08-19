#include "sonic.h"
#include "timer.h"
#include "lcd.h"

void sonic_init()
{
	LPC_IOCON->P1_4 = 0x0;
	LPC_IOCON->P1_17 = 0x0;
	LPC_IOCON->P1_18 = 0x0;
}

//returns distance from sensor (1, 2, 3) to obstacle in cm
uint8_t sonic_measure(volatile uint8_t sensor){
	
	volatile uint32_t sensor_shift;
	point p;
	uint8_t distance;
	volatile uint32_t stat = 0;
	volatile uint16_t count = 0;
	
	switch(sensor)
	{
		case 1: sensor_shift = 4;
						p.x = 0;
						p.y = 0;
						break;
						
		case 2:	sensor_shift = 18;
						p.x = 109;
						p.y = 0;
						break;
						
		case 3:	sensor_shift = 17;
						p.x = 229; 
						p.y = 0;
						break;
	}
	
	LPC_GPIO1->DIR |= 1 << sensor_shift;
	LPC_GPIO1->SET |= 1 << sensor_shift;
	
	timer_start();
	while(LPC_TIM0->TC < 15);
	timer_stop();
	
	LPC_GPIO1->CLR |= 1 << sensor_shift;
	LPC_GPIO1->DIR ^= 1 << sensor_shift;
	
	while(!stat){
		stat = LPC_GPIO1->PIN & (1<<sensor_shift);
	}
	
	timer_start();
	while(stat){
		stat = LPC_GPIO1->PIN & (1<<sensor_shift);
	}
	count = timer_stop();
	count /= 58;
	distance = count;
	
	if(count > 128){
		count = 128;		
	}
		
	return distance;
}


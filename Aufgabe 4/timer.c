#include "timer.h"

void timer_init()
{
	volatile uint32_t *pconp = (uint32_t *) 0x400FC0C4;
	*pconp |= 1 << 1;	
	
	LPC_TIM0->TC = 0;
	LPC_TIM0->PR = 0x1E; //30 instructionas = 1µs
	LPC_TIM0->PC = 0;
	LPC_TIM0->MCR = 0;
	
}

void timer_start()
{
	LPC_TIM0->TC = 0;
	LPC_TIM0->PC = 0;
	
	//start des timers
	LPC_TIM0->TCR = 1;		
}



uint32_t timer_stop()
{
	LPC_TIM0->TCR = 0;	
	return LPC_TIM0->TC;
}


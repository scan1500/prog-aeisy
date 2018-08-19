#include "motor.h"

void mtr_init(){
	
	LPC_IOCON->P1_23 = 0;	
	LPC_IOCON->P1_24 = 0;	
	LPC_IOCON->P1_25 = 0;	
	LPC_IOCON->P1_26 = 0;	

	//LPC_IOCON->P1_20 = 0x2;	
	//LPC_IOCON->P1_21 = 0x2;	
	
	
}

#include "compass.h"

void cmp_init() {
	uint32_t *pconp = (uint32_t *) 0x400FC0C4;
	*pconp |= 1 << 4;
	
	// enable dlab for baudrate-configuraiton
	LPC_UART1->LCR |= 1 << 7;
	
	// considering pclk is at 30 Mhz
	// dlm = 0, dll = 195 -> baud 9600
	LPC_UART1->DLM = 0;
	LPC_UART1->DLL = 195;
	
	// 8 bit word-length, 2 stop bits, no parity
	LPC_UART1->LCR |= 7;
	
	// FIFO enable
	LPC_UART1->FCR |= 1;
	
	// disable dlab
	LPC_UART1->LCR ^= 1 << 7;
	
	// Set Pin mode to UART
	LPC_IOCON->P2_0 |= 2; // U1_TXD
	LPC_IOCON->P2_1 |= 2; // U1_RXD
	
}

int get_dir(void) {
	hilo angle;
	while(!(LPC_UART1->LSR & (1 << 5)));
	LPC_UART1->THR = 0x13;
	while(!(LPC_UART1->LSR & 	1));
	angle.u8[1] = LPC_UART1->RBR;
	while(!(LPC_UART1->LSR & 	1));
	angle.u8[0] = LPC_UART1->RBR;
	
	return angle.u16;
}

int get_pitch(void) {
}

int get_roll(void) {
}
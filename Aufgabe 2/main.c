#include <stdint.h>
#include <LPC177x_8x.H>
#include <math.h>
#include <stdlib.h>

typedef union
{
	uint16_t u16;
	uint8_t u8[2];
} hilo;

//LCD configuration
volatile uint8_t *lcd_data = (volatile uint8_t *) 0x80004000;
volatile uint8_t *lcd_cmd = (volatile uint8_t *) 0x80004004;

unsigned char panzer_bild[]={0,0,0,0,0,0,0,0,0,0,0,31,255,240,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 3,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,15,255,255,255,224,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 15,255,255,255,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,15,255,255,255,224,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 15,255,255,255,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,127,255,255,255,255,255,255,255,248,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255 , 255,255,255,255,255,255,255,248,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,1,255,255,255,255,255,255,255,255,248,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,255 , 255,255,255,255,255,255,255,248,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,3,255,255,255,255,255,255,255,255,252,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,255 , 255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,7,255,255,255,255,255,255,255,255,255,254,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,255 , 255,255,255,255,255,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,31,255,255,255,255,255,255,255,255,255,255,192 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,255 , 255,255,255,255,255,255,255,255,255,192,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,31,255,255,255,255,255,255,255,255,255,255,224 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,248,0,0,0,15,252 , 0,0,0,0,0,0,0,0,127,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,0,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252 , 0,0,0,0,0,0,0,1,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,1,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252 , 0,0,0,0,0,0,0,3,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,3,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252 , 0,0,0,0,0,0,0,15,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,15,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252 , 0,0,0,0,0,0,0,31,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,31,255,255 , 255,255,255,255,255,255,255,255,255,255,224,0,0,0,0,0,0,0,15,252 , 0,0,0,0,0,0,0,63,255,255,255,255,255,255,255,255,255,255,255,224 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,255,255 , 255,255,255,255,255,255,255,255,255,192,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,127,255,255,255,255,255,255,255,255,255,255,255,128 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255 , 255,255,255,255,255,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,1,255,255,255,255,255,255,255,255,255,255,255,254,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,255,255,255 , 255,255,255,255,255,255,255,255,224,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,1,255,255,255,255,255,255,255,255,255,255,255,224,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255 , 255,255,255,255,255,255,255,255,224,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,7,255,255,255,255,255,255,255,255,255,255,255,224,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,255,255,255 , 255,255,255,255,255,255,255,255,240,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,31,255,255,255,255,255,255,255,255,255,255,255,240,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,255,255,255 , 255,255,255,255,255,255,255,255,240,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,3,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,248,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0 , 0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,192,0,0,0,0,0,0,0,0,3,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,192,0,0,0,0,0,0 , 0,0,15,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,240,0,0,0,0,0,0,0,0,127,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0 , 0,7,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,128,0,0,0,0,0,0,31,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,192,0,0,0,0,0 , 0,63,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,240,0,0,0,0,0,1,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,248,0,0,0,0,0 , 3,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,248,0,0,0,0,0,3,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,248,0,0,0,0,0 , 3,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,255,255,248,0,0,0,0,0,3,255,255,255,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,255,255,248,0,0,0,0,0 , 3,255,199,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,254,127,248,0,0,0,0,0,3,254,0,127,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,224,7,252,0,0,0,0,0 , 7,252,0,63,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,192,3,252,0,0,0,0,0,15,240,0,15,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,0,0,0 , 15,224,0,7,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,252,0,0,127,0,0,0,0,0,31,192,0,3,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,252,0,0,63,128,0,0,0,0 , 63,128,0,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,248,0,0,31,128,0,0,0,0,63,128,0,1,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,248,0,0,31,192,0,0,0,0 , 63,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,240,0,0,15,224,0,0,0,0,126,0,0,0,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,224,0,0,15,224,0,0,0,0 , 126,0,126,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,224,7,224,15,248,0,0,0,0,126,0,126,0,127,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,224,7,224,6,248,0,0,0,0 , 254,0,255,0,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,224,15,240,6,248,0,0,0,0,254,0,255,0,127,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,224,15,240,7,240,0,0,0,0 , 254,0,255,0,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,224,15,240,7,248,0,0,0,0,126,0,255,0,121,255,255,255,255,255 , 63,255,255,255,255,239,255,255,127,255,251,224,15,240,7,240,0,0,0,0 , 126,0,126,0,96,31,254,0,255,240,7,255,192,63,254,0,255,240,7,255 , 128,96,7,224,7,240,0,0,0,0,62,0,124,0,224,15,248,0,63,224 , 1,254,0,7,248,0,127,192,3,254,0,96,7,192,15,224,0,0,0,0 , 62,0,0,0,224,3,240,0,31,128,0,252,0,7,240,0,31,128,0,252 , 0,96,0,0,15,224,0,0,0,0,63,0,0,0,192,0,224,0,14,0 , 0,56,0,1,128,0,15,0,0,48,0,48,0,0,15,128,0,0,0,0 , 63,0,0,0,192,0,224,0,30,0,0,28,0,3,128,0,7,0,0,96 , 0,48,0,0,15,128,0,0,0,0,63,192,0,3,128,0,112,0,28,0 , 0,28,0,7,128,0,3,128,0,224,0,60,0,0,63,128,0,0,0,0 , 31,224,0,3,128,0,48,0,24,0,0,6,0,6,0,0,1,128,1,192 , 0,28,0,0,63,0,0,0,0,0,31,224,0,7,0,0,48,0,48,0 , 0,6,0,6,0,0,1,192,1,192,0,14,0,0,255,0,0,0,0,0 , 15,240,0,14,0,0,24,0,48,0,0,6,0,6,0,0,1,192,3,128 , 0,7,0,0,254,0,0,0,0,0,7,252,0,124,15,128,24,252,48,3 , 224,7,31,140,0,252,0,227,243,128,63,135,192,7,254,0,0,0,0,0 , 3,255,129,248,31,128,24,254,112,7,240,7,63,204,0,254,0,231,243,0 , 63,129,248,31,248,0,0,0,0,0,1,255,255,224,63,192,29,255,112,7 , 248,7,63,204,0,254,0,239,243,0,63,192,127,255,248,0,0,0,0,0 , 0,253,255,192,63,192,29,255,112,7,248,3,127,204,1,255,0,239,243,0 , 63,192,63,255,240,0,0,0,0,0,0,126,127,128,63,192,29,255,112,7 , 248,3,127,204,1,255,0,239,243,0,63,192,31,199,224,0,0,0,0,0 , 0,63,1,128,63,192,25,255,112,7,240,7,63,204,0,254,0,231,243,0 , 63,192,24,15,128,0,0,0,0,0,0,31,193,192,31,128,24,254,112,3 , 240,7,31,204,0,252,0,231,243,128,63,128,24,31,128,0,0,0,0,0 , 0,15,225,192,15,128,24,124,48,3,224,7,15,140,0,120,1,227,227,128 , 31,0,56,127,0,0,0,0,0,0,0,7,240,192,0,0,24,0,48,0 , 0,6,0,6,0,0,1,192,1,128,0,0,56,124,0,0,0,0,0,0 , 0,1,248,192,0,0,48,0,24,0,0,6,0,6,0,0,1,192,1,192 , 0,0,112,252,0,0,0,0,0,0,0,0,252,192,0,0,48,0,24,0 , 0,12,0,7,0,0,1,128,1,192,0,0,113,248,0,0,0,0,0,0 , 0,0,127,112,0,0,240,0,28,0,0,28,0,7,128,0,3,128,0,224 , 0,0,231,240,0,0,0,0,0,0,0,0,63,248,0,0,224,0,14,0 , 0,60,0,3,128,0,7,0,0,112,0,0,199,192,0,0,0,0,0,0 , 0,0,31,248,0,0,224,0,14,0,0,56,0,1,192,0,15,0,0,56 , 0,1,223,192,0,0,0,0,0,0,0,0,15,252,0,3,240,0,31,0 , 0,124,0,3,224,0,31,0,0,124,0,7,191,128,0,0,0,0,0,0 , 0,0,7,255,128,15,252,0,127,224,3,255,128,15,248,0,255,224,3,255 , 0,31,255,0,0,0,0,0,0,0,0,0,3,255,224,126,31,1,240,252 , 15,199,192,124,31,1,241,248,15,135,224,127,252,0,0,0,0,0,0,0 , 0,0,0,255,255,248,15,255,224,63,255,1,255,248,15,255,192,127,254,3 , 255,255,248,0,0,0,0,0,0,0,0,0,0,127,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,255,240,0,0,0,0,0,0,0 , 0,0,0,7,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,255,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,252,0,0,0,0,0,0,0,0 , 0,0,0,0,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 , 255,224,0,0,0,0,0,0,0,0,0,0,0,0,31,255,255,255,255,255 , 255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0};
uint8_t table[]={7,6,5,4,3,2,1,0};
	
int lcd_rdy();
void lcd_init();
int set_pixel(uint16_t x, uint16_t y);
void lcd_write(char c);
void send_d2_cmd(uint8_t d1, uint8_t d2, uint8_t cmd);
void send_d1_cmd(uint8_t d1, uint8_t cmd);
void send_cmd(uint8_t cmd);
void lcd_clr();
uint8_t lcd_print_string(char *string);
int load_bmp(uint8_t* img);
void draw_circle(uint16_t mx, uint16_t my);
void draw_triangle(uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by, uint16_t cx, uint16_t cy);
	



int main(int argc, char** argv) {
	
	uint16_t i;
	lcd_init();
	
	//char* string = "#DAEMON";
	//lcd_print_string(string);
	//load_bmp(panzer_bild);
	lcd_clr();
	
	
	//for(i=20; i<=239; i++){
	//	set_pixel(i,0);
	//}

	
	draw_triangle(20, 108, 220, 108, 120, 20);
	//draw_circle(120, 64);
	
	
	while(1);		
	
}

int load_bmp(unsigned char* img){
	uint16_t i;
	
	//set address pointer to graphic home
	send_d2_cmd(0,0x02,0x24);	
	
	for(i=0; i<3840; i++)
			send_d1_cmd(img[i], 0xC0);
	
}

int set_pixel(uint16_t x, uint16_t y){
		
	hilo addr;
	uint16_t indexpos;
	uint8_t high, low, cmd, setbit;
	
	cmd = 0xF8;
	setbit = x%8;
	
	cmd |= table[x%8];
	indexpos = (((x/8))+(30*y)) + 0x0200;
		
	addr.u16 = indexpos;
	high = addr.u8[1];
	low = addr.u8[0];
	
	send_d2_cmd(low,high,0x24);	
	send_cmd(cmd);
	
}

void lcd_init(){
	
	//F�r P4.0-P4.15 pul-up resistor und hysteresis aktiviert und als adress bus gesetzt 
	//->              0x10        +      0x20					+							0x01 = 0x31
	LPC_IOCON->P4_0 = 0x31;
	LPC_IOCON->P4_1 = 0x31;
	LPC_IOCON->P4_2 = 0x31;
	LPC_IOCON->P4_3 = 0x31;
	LPC_IOCON->P4_4 = 0x31;
	LPC_IOCON->P4_5 = 0x31;
	LPC_IOCON->P4_6 = 0x31;
	LPC_IOCON->P4_7 = 0x31;
	LPC_IOCON->P4_8 = 0x31;
	LPC_IOCON->P4_9 = 0x31;
	LPC_IOCON->P4_10 = 0x31;
	LPC_IOCON->P4_11 = 0x31;
	LPC_IOCON->P4_12 = 0x31;
	LPC_IOCON->P4_13 = 0x31;
	LPC_IOCON->P4_14 = 0x31;
	LPC_IOCON->P4_15 = 0x31;
	
	//F�r P4.24 pulup resistor und hysteresis aktiviert und out enable gesetzt
	//F�r P4.25 Pulup resistor und hysteresis aktiviert und write enable gesetzt
	//F�r P4.30 pulup resistor und hysteresis aktiviert und write enable gesetzt
	LPC_IOCON->P4_24 = 0x31;
	LPC_IOCON->P4_25 = 0x31;
	LPC_IOCON->P4_30 = 0x31;
	
	//F�r P3.0-P3.7 pulup resistor und hysteresis aktiviert und als data bus gesetzt
	LPC_IOCON->P3_0 = 0x31;
	LPC_IOCON->P3_1 = 0x31;
	LPC_IOCON->P3_2 = 0x31;
	LPC_IOCON->P3_3 = 0x31;
	LPC_IOCON->P3_4 = 0x31;
	LPC_IOCON->P3_5 = 0x31;
	LPC_IOCON->P3_6 = 0x31;
	LPC_IOCON->P3_7 = 0x31;
	
	//Enable the power supply for the external memory interface (register PCONP)
	uint32_t *pconp = (uint32_t *) 0x400FC0C4;
	*pconp |= 1 << 11;
	
	LPC_EMC->Control = 0x01;
	
	//EMCStaticMemoryConfiguration
	LPC_EMC->StaticConfig0 = 0x80;
	
	//set text home address
	send_d2_cmd(0, 0, 0x40);

	//set text are to 30(30)
	send_d2_cmd(0x1E, 0, 0x41);
	
	//Set Graphic Home Address to 0x0200
	send_d2_cmd(0, 0x02, 0x42);
	
	//set graphic area to 30 (decimal) = 30 bytes per line
	send_d2_cmd(0x1E, 0, 0x43);
	
	//Activate the EXOR modus (overlapping pixels of text and graphics memory are combined via XOR)
	send_cmd(0x81);
		
	//Set Display Mode for text and Graphics to ON
	send_cmd(0x9c);
	
	//Set address pointer to zero
	send_d2_cmd(0,0,0x24);
	
	lcd_clr();
	
}

uint8_t lcd_print_string(char *string){
	//set address pointer to zero (=text area)
	send_d2_cmd(0,0,0x24);
	
	char *c = &string[0];	
	while(*c != '\0'){		
		lcd_write(*c);
		c++;
	}
	return 0;
}

//write a char to display
void lcd_write(char c){
	
	//Falsche ASCI-Tabelle am LCD dem Huan
	char out = (char) (c-0x20);
	send_d1_cmd(out, 0xC0);

}

void lcd_clr(){
	//Set address pointer
	send_d2_cmd(0, 0, 0x24);
	
	//Fill lcd with 0 (clear)
	for(int i=0; i<4880; i++)
		send_d1_cmd(0, 0xC0);
	
	//Set address pointer
	send_d2_cmd(0, 0, 0x24);
}

int lcd_rdy(){
	volatile uint8_t state;
	do {
		state = *lcd_cmd; //  & 0x3); //  == 0x3;
		state &= 0x03;
	} while(state != 0x03);
	return state;
}

void send_cmd(uint8_t cmd){
	while(!lcd_rdy());
	*lcd_cmd=cmd;
}

void send_d1_cmd(uint8_t d1, uint8_t cmd){
	while(!lcd_rdy());
	*lcd_data=d1;
	while(!lcd_rdy());
	*lcd_cmd=cmd;
}

void send_d2_cmd(uint8_t d1, uint8_t d2, uint8_t cmd){
	while(!lcd_rdy());
	*lcd_data=d1;
	while(!lcd_rdy());
	*lcd_data=d2;
	while(!lcd_rdy());
	*lcd_cmd=cmd;
}

void draw_circle(uint16_t mx, uint16_t my)
{
	uint16_t x, y;
	for(y=0; y < 128; y++)
		for(x=0; x < 240; x++)
			if(sqrt(pow(abs(mx-x),2) + pow(abs(my-y),2)) < 50)
				set_pixel(x, y);
}

void draw_triangle(uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by, uint16_t cx, uint16_t cy)
{
	// PRECALC. DISTANCES BETWEEN POINTS
	uint16_t distanceAB_X = bx - ax, distanceAB_Y = by - ay;
	uint16_t distanceBC_X = cx - bx, distanceBC_Y = cy - by;
	uint16_t distanceCA_X = ax - cx, distanceCA_Y = ay - cy;
	
	// PRECALC CROSS PRODUCS
	uint16_t crossMulAB = (bx*ay)-(by*ax);
	uint16_t crossMulBC = (cx*by)-(cy*bx);
	uint16_t crossMulCA = (ax*cy)-(ay*cx);
	
	uint16_t x, y;
	for(y = 0; y <= 128; y++)
		for(x = 0; x <= 240; x++)
			if((distanceAB_Y)*x-(distanceAB_X)*y+crossMulAB >= 0 
			&& (distanceBC_Y)*x-(distanceBC_X)*y+crossMulBC >= 0 
			&& (distanceCA_Y)*x-(distanceCA_X)*y+crossMulCA >= 0)
				set_pixel(x, y);
}


#include "lcd.h"
#include <stdio.h>

volatile uint8_t *lcd_data = (volatile uint8_t *) 0x80004000;
volatile uint8_t *lcd_cmd = (volatile uint8_t *) 0x80004004;

uint8_t table[]={7,6,5,4,3,2,1,0};

void load_bmp(unsigned char* img){
	uint16_t i;
	
	//set address pointer to graphic home
	send_d2_cmd(0,0x02,0x24);	
	
	for(i=0; i<3840; i++)
			send_d1_cmd(img[i], 0xC0);
}

void clr_pixel(uint16_t x, uint16_t y){
		
	hilo addr;
	uint16_t indexpos;
	uint8_t high, low, cmd;
	
	cmd = 0xF0;
	
	cmd |= table[x%8];
	indexpos = (((x/8))+(30*y)) + 0x0200;
		
	addr.u16 = indexpos;
	high = addr.u8[1];
	low = addr.u8[0];
	
	send_d2_cmd(low,high,0x24);	
	send_cmd(cmd);
	
}

void set_pixel(uint16_t x, uint16_t y){
		
	hilo addr;
	uint16_t indexpos;
	uint8_t high, low, cmd;
	
	cmd = 0xF8;
	
	cmd |= table[x%8];
	indexpos = pixel_xy_to_addr(x,y);
	indexpos = (((x/8))+(30*y)) + 0x0200;
		
	addr.u16 = indexpos;
	high = addr.u8[1];
	low = addr.u8[0];
	
	send_d2_cmd(low,high,0x24);	
	send_cmd(cmd);
	
}

uint16_t text_xy_to_addr(uint32_t x, uint32_t y){
		//return (((x/8))+(30*y));// + 0x0200;	
		return (x + (30 * y));
}

uint16_t pixel_xy_to_addr(uint32_t x, uint32_t y){
		return (((x/8))+(30*y)) + 0x0200;	
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

	//set text area to 30(30)
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

uint8_t lcd_print_string(char *string, int x, int y){
	
	hilo addr;
	uint8_t high, low;

	addr.u16 = text_xy_to_addr(x, y);
	high = addr.u8[1];
	low = addr.u8[0];

	//set address pointer to zero (=text area)
	send_d2_cmd(low,high,0x24);
	
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

void draw_circle(point *center, uint16_t rad, uint8_t fill)
{
	uint16_t x;
	uint16_t y;
	if(fill)
	{
		for(y=0; y < 128; y++)
		{
			for(x=0; x<240; x++)
			{
				if(sqrt(pow(abs(center->x-x),2) + pow(abs(center->y-y),2)) < rad)
				{
					set_pixel(x, y);
				}
			}
		}
	}
	else
	{
		for(y=0; y < 128; y++)
		{
			for(x=0; x<240; x++)
			{
				if((sqrt(pow(abs(center->x-x),2) + pow(abs(center->y-y),2)) < rad) && (sqrt(pow(abs(center->x-x),2) + pow(abs(center->y-y),2)) > rad-1))
				{
					set_pixel(x, y);
				}
			}
		}
	}
}

void draw_triangle(point *a, point *b, point *c)
{
	// PRECALC. DISTANCES BETWEEN POINTS
	int16_t distanceAB_X = b->x - a->x, distanceAB_Y = b->y - a->y;
	int16_t distanceBC_X = c->x - b->x, distanceBC_Y = c->y - b->y;
	int16_t distanceCA_X = a->x - c->x, distanceCA_Y = a->y - c->y;
	
	// PRECALC CROSS PRODUCS
	int16_t crossMulAB = (b->x*a->y)-(b->y*a->x);
	int16_t crossMulBC = (c->x*b->y)-(c->y*b->x);
	int16_t crossMulCA = (a->x*c->y)-(a->y*c->x);
	
	int16_t x, y;
	for(y = 0; y < 128; y++)
		for(x = 0; x < 240; x++)
			if((distanceAB_Y)*x-(distanceAB_X)*y+crossMulAB >= 0 
			&& (distanceBC_Y)*x-(distanceBC_X)*y+crossMulBC >= 0 
			&& (distanceCA_Y)*x-(distanceCA_X)*y+crossMulCA >= 0)
				set_pixel(x, y);
}

void draw_rectangle(point *upper_left, uint8_t length, uint8_t width, uint8_t fill)
{
	uint8_t x;
	uint8_t y;
	
	if(fill)
	{
		for(y=upper_left->y; y<=upper_left->y+length; y++)
		{
			for(x=upper_left->x; x<=upper_left->x+width; x++)
			{
				set_pixel(x,y);
			}
		}
	}
	else
	{
		for(x=upper_left->x, y=upper_left->y; x<upper_left->x+width; x++)
		{
			set_pixel(x,y);
			set_pixel(x,y+length);
		}
		for(x=upper_left->x, y=upper_left->y; y<=upper_left->y+length; y++)
		{
			set_pixel(x,y);
			set_pixel(x+width,y);
		}
	}
}

void int_to_string(char *string, int i){
	int j;
	volatile int digits = count_digits(i);
	string[3] = '\0';
	for(j=2 ; j >= 0; j--){
		string[j] = 0x30 + (i % 10);
		i /= 10;	
	}
}

int count_digits(int i){
	if(i>=1000000000) return 10;
	if(i>=100000000) return 9;
	if(i>=1000000) return 7;
	if(i>=100000) return 6;
	if(i>=10000) return 5;
	if(i>=1000) return 4;
	if(i>=100) return 3;
	if(i>=10) return 2;
	return 1;		
}

void clr_rectangle(point *upper_left, uint8_t length, uint8_t width, uint8_t fill)
{
	uint8_t x;
	uint8_t y;
	
	for(y=upper_left->y; y<=upper_left->y+length; y++)
	{
		for(x=upper_left->x; x<=upper_left->x+width; x++)
		{
			clr_pixel(x,y);
		}
	}
}

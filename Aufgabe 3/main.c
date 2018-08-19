#include <stdint.h>
#include <LPC177x_8x.H>
#include <stdlib.h>
#include "lcd.h"
#include "images.h"
#include "sonic.h"

int main(int argc, char** argv) {
	
	uint16_t i;
	lcd_init();
	sonic_init();
	
	//char* string = "#DAEMON";
	//lcd_print_string(string);
	//load_bmp(panzer_bild);
	lcd_clr();
	
	
	//for(i=20; i<=239; i++){
	//	set_pixel(i,0);
	//}

	
	//draw_circle(130, 64);
//	draw_triangle(20, 108, 220, 108, 120, 20);
	
	point a = {.x = 10, .y = 1};
	point b = {.x = 240, .y  = 128};
	point c = {.x = 120, .y = 0};
	point m = {.x = 120, .y = 64};
	
	//draw_triangle(&a, &b, &c);
	//draw_circle(&m, 64, 0);
	//draw_rectangle(&a, 20, 30, 0);


	while(1) {
		sonic_measure(1);
	}

	
	while(1);		
	
}

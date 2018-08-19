#include <stdint.h>
#include <LPC177x_8x.H>
#include <stdlib.h>
#include "lcd.h"
#include "images.h"
#include "sonic.h"
#include "timer.h"
#include "compass.h"

int main(int argc, char** argv) {
	
	uint16_t i;
	uint8_t dist1,dist2,dist3;
	lcd_init();
	timer_init();
	sonic_init();
	cmp_init();
	
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
		point p1 = { .x = 0, .y = 10};
		point p2 = { .x = 32, .y = 10};
		point p3 = { .x = 65, .y = 10};
		
		dist1 = sonic_measure(1);
		dist2 = sonic_measure(2);
		dist3 = sonic_measure(3);
		char str_dist[4];
		str_dist[3] = '\0';
		char str_dir[4];
		str_dir[3] = '\0';


		
		int_to_string(str_dist,dist1);
		lcd_print_string(str_dist,0,0);
		if(dist1 > 128) {
			dist1 = 128;
		}
		draw_rectangle(&p1, dist1, 10, 1);		
		
		int_to_string(str_dist,dist2);
		lcd_print_string(str_dist,4,0);
		if(dist2 > 128) {
			dist2 = 128;
		}
		draw_rectangle(&p2, dist2, 10, 1);		
		
		int_to_string(str_dist,dist3);
		lcd_print_string(str_dist,8,0);
		if(dist3 > 128) {
			dist3 = 128;
		}
		draw_rectangle(&p3, dist3, 10, 1);
		

		timer_start();
		while(LPC_TIM0->TC < 100000);
		timer_stop();

		
		volatile uint16_t angle = get_dir()/10;
		int_to_string(str_dir,angle);
		lcd_print_string(str_dir,12,1);	
		//lcd_print_string("jugendfrei",60,100);	
		
		clr_rectangle(&p1, dist1, 10, 1);

		clr_rectangle(&p2, dist2, 10, 1);

		clr_rectangle(&p3, dist3, 10, 1);
			
		
	}
	
	while(1);		
	
}
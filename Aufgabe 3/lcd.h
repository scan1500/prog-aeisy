#ifndef __LCD_H__
#define __LCD_H__
#include <stdlib.h>
#include <stdint.h>
#include <LPC177x_8x.H>
#include <math.h>


typedef union
{
	uint16_t u16;
	uint8_t u8[2];
} hilo;

typedef struct point
{
	uint16_t x;
	uint16_t y;
	
} point;


//LCD configuration
extern volatile uint8_t *lcd_data;
extern volatile uint8_t *lcd_cmd;

extern uint8_t table[];
	
int lcd_rdy(void);
void lcd_init(void);
void set_pixel(uint16_t x, uint16_t y);
void clr_pixel(uint16_t x, uint16_t y);
void lcd_write(char c);
void send_d2_cmd(uint8_t d1, uint8_t d2, uint8_t cmd);
void send_d1_cmd(uint8_t d1, uint8_t cmd);
void send_cmd(uint8_t cmd);
void lcd_clr(void);
uint8_t lcd_print_string(char *string);
void load_bmp(uint8_t* img);
void draw_circle(point *center, uint16_t rad, uint8_t fill);
void draw_triangle(point *a, point *b, point *c);
void draw_rectangle(point *upper_left, uint8_t length, uint8_t width, uint8_t fill);
void clr_rectangle(point *upper_left, uint8_t length, uint8_t width, uint8_t fill);

#endif

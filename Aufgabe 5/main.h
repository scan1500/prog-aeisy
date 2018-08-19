#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdint.h>
#include <LPC177x_8x.H>
#include <stdlib.h>
#include "lcd.h"
#include "images.h"
#include "sonic.h"
#include "timer.h"
#include "compass.h"
#include "motor.h"


void init(void);
int main(void); 
void measure_display_sonics(void);
void measure_display_angle(void);
void measure_display_roll(void);
void measure_display_pitch(void);


#endif


#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdlib.h>
#include <stdint.h>
#include <LPC177x_8x.H>

void timer_init();
void timer_start();
uint32_t timer_stop();

#endif
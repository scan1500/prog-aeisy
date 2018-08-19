#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdlib.h>
#include <stdint.h>
#include <LPC177x_8x.H>

void timer_init(void);
void timer_start(void);
uint32_t timer_stop(void);

#endif


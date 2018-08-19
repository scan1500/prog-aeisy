#ifndef __SONIC_H__
#define __SONIC_H__
#include <stdlib.h>
#include <stdint.h>
#include <LPC177x_8x.H>
#include <math.h>

void sonic_init();
void sonic_measure(uint8_t sensor);

#endif

#ifndef __COMPASS_H__
#define __COMPASS_H__
#include <stdint.h>
#include <LPC177x_8x.H>
#include "helpers.h"

#define GET_ANGLE 0x13
#define GET_PITCH 0x14
#define GET_ROLL	0x15

void cmp_init(void);
uint16_t get_dir(void);
int8_t get_pitch(void);
int8_t get_roll(void);

#endif



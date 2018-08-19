#ifndef __COMPASS_H__
#define __COMPASS_H__
#include <stdint.h>
#include <LPC177x_8x.H>
#include "helpers.h"

void cmp_init(void);
int get_dir(void);
int get_pitch(void);
int get_roll(void);

#endif
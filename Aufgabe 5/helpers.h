#ifndef __HELPERS_H__
#define __HELPERS_H__
#include <stdint.h>
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

void int_to_string(char *string, int src, int len);

#endif

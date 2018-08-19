#include "helpers.h"

//converts a given positive number src with length len to into a string with ending '\0'
//ensure *string is big enough for the number
void int_to_string(char *string, int src, int len){
	int i;
	string[len] = '\0';
	for(i=len-1 ; i >= 0; i--){
		string[i] = 0x30 + (src % 10);
		src /= 10;	
	}
}
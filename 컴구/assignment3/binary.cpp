#include "binary.h"
#include <string.h>
#include <stdlib.h>
unsigned int extend(short int X, bool sign_extend){
	if (sign_extend){
		unsigned int sign = X>>15;

		if (sign){
			unsigned short int uX = static_cast<unsigned int>(X);
			return 0xFFFF0000+uX;
		}
	}
	unsigned int blank = 0;
	return blank+X;
}

unsigned int cut(unsigned int X, int lcut, int rcut){
	return (X<<lcut)>>lcut>>rcut;
}
unsigned int char2int(char* word){
	if(word[0] == '0' and word[1] == 'x'){
		unsigned int retval = strtoul(word, nullptr, 16);
		return retval;
	}
	return atoi(word);
}


#ifndef FILTER_H_
#define FILTER_H_

#include "bmp.h"

typedef struct BoxFilter {
	int filter[3][3];
	float norm;
} BoxFilter;

Pixel calculateBlur(BMPImage * image, int i, int j);

BMPImage * blur(BMPImage * image);
#endif

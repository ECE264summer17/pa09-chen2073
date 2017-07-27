#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image) {

	BMPImage * blurImage = malloc(sizeof(BMPImage));

	blurImage->header = image->header;
	
	blurImage->norm_height = image->norm_height;

	blurImage->pixels = malloc(sizeof(Pixel *) * image->norm_height);
	
	int i;
	for(i=0; i < image->norm_height; i++)
	{
		blurImage->pixels[i] = malloc(sizeof(Pixel) * (image->header.width_px));
	}

	int j;
	for(i=0; i < image->norm_height; i++)
	{
		for(j=0; j < image->header.width_px; j++)
		{
			blurImage->pixels[i][j] = calculateBlur(image, i, j);	
		}
	}

	return blurImage;
}
#endif


Pixel calculateBlur(BMPImage * image, int i, int j)
{
	Pixel blurPixel;
	blurPixel.alpha = 255;
	int blue = 0;
	int green = 0;
	int red = 0;

	int m, n;
	for(m = -1; m <= 1; m++)
	{
		for(n = -1; n <= 1; n++)
		{
			int p = i + m;
			int q = j + n;

			if(p < 0) {p = 0;}
			
			if(q < 0) {q = 0;}

			if(p >= image->norm_height) {p = image->norm_height - 1;}

			if(q >= image->header.width_px) {q = image->header.width_px - 1;}

			blue += image->pixels[p][q].blue;
			green += image->pixels[p][q].green;
			red += image->pixels[p][q].red;
		}
	}


		blurPixel.blue = blue / 9;
		blurPixel.green = green / 9;
		blurPixel.red = red / 9; 

return blurPixel;
}



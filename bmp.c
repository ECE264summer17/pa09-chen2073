#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) 
{
	//allocate image type
	BMPImage * image = malloc(sizeof(BMPImage));
	
	fread(&(image->header), sizeof(image->header), 1, fp);

	//assign normal height
	image->norm_height = abs(image->header.height_px);

	//allocate rows
	image->pixels = malloc(sizeof(Pixel *) * image->norm_height);
	
	//allocate columns
	int i;
	for(i=0; i < image->norm_height; i++)
	{
		image->pixels[i] = malloc(sizeof(Pixel) * (image->header.width_px));
	}
	

	//initialize pixel channel
	int j;
	for(i = 0; i < image->norm_height; i++)
	{
		for(j = 0; j < image->header.width_px; j++)
		{
			fread(&(image->pixels[i][j]), sizeof(Pixel), 1, fp);
		}
	}

	return image;		
}

void freeImage(BMPImage * image) 
{
	int i;
	//free columns
	for(i=0; i < image->norm_height; i++)
	{
		free(image->pixels[i]);
	}
	//free rows
	free(image->pixels);
	
	free(image);
}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) 
{
	fwrite(&(image->header), sizeof(BMPHeader), 1, fp);

	int i, j;
	for(i = 0; i < image->norm_height; i++)
	{
		for(j = 0; j < image->header.width_px; j++)
		{
			fwrite(&(image->pixels[i][j]), sizeof(Pixel), 1, fp);
		}
	}
	
return;
}
#endif

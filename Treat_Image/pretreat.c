#include "pretreat.h"
#include "pixel_operations.h"
void ToGrayScale(SDL_Surface *img)
{
	Uint32 pixel;
	Uint8 r,g,b;
	unsigned long luminance;
	for(int i = 0;i<img->w;i++)
		for(int j = 0;j<img->h;j++)
		{
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel,img->format, &r, &g, &b);
			luminance =  0.3*r + 0.59*g + 0.11*b;
			r = b = g = luminance;
			pixel = SDL_MapRGB(img->format,r,g,b);
			putpixel(img,i,j,pixel);
		}
}

void Binarize(SDL_Surface* img)
{
	Uint32 pixel;
	Uint8 r, g, b, bw;  
	Uint8 average;	
	for(unsigned int i = 0; i<(unsigned int)img->w; i++)
		for(unsigned int j = 0; j<(unsigned int)img->h; j++)
		{
			pixel = getpixel(img, i, j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			average = (r + g + b)/3;
			if (average<128)
				bw = 0;
			else
				bw = 255;
			pixel = SDL_MapRGB(img->format, bw, bw, bw);
			putpixel(img, i, j, pixel);
		}
}




#include <stdlib.h>
#include <stdio.h>
#include "pixel_operations.h"
#include "segmentation.h"

/*int *array = calloc(len, sizeof (int));
 * free(array);
*/
Uint8 HHisto(SDL_Surface *img, int begin, int h, int w, Uint8 histo[])
{
	Uint32 pixel;
	Uint8 r,g,b;
	int cpt;
	for(int j = begin ; j < begin+h ; j++)
	{
		cpt = 0;
		for(int i = begin; i < begin + w ; i++)
		{
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			cpt+=r;
		}
		
		histo[j] = cpt/w;
	}
	return *histo;
}

void FindLines(SDL_Surface *img, Uint8 histo[])
{
	Uint32 pixel;
	Uint8 r,g,b;
	for(int j = 0 ; j < img->h ; j++)
	{
		if (histo[j]==255)
			for(int i = 0; i < img->w ; i++)
			{
				pixel = getpixel(img,i,j);
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, 255, 0, 0);
				putpixel(img, i, j, pixel);
			}
	}
}

                                                                            								                     

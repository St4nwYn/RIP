#include <stdlib.h>
#include <stdio.h>
#include "pixel_operations.h"
#include "segmentation.h"

/*int *array = calloc(len, sizeof (int));
 * free(array);
 * int *begin = array, *end = array + len;
*/
void HHisto(SDL_Surface *img, int be, int h, int w, int *histo , int *p)
{
	Uint32 pixel;
	Uint8 r,g,b,average;
	int sum, cpt = 0;
	for(int j = be ; j < be+h ; j++)
	{
		sum = 0;
		for(int i = be; i < be + w ; i++)
		{
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			sum+=r;
		}
		average = sum/w;
		
		if (average!=255)
		{			
			*(histo + cpt) = j;
			//printf("%d\n",*(histo + cpt));
			cpt++;			
		}	
	}
	*p = cpt;
}

void List2Struct(int *histo, Coord *box, int *p, int size)
{
	int cpt = 0, boxcpt = 0;
	Coord coordBox;
	 
	for(int i = 0; i < *p-1; i++)
	{			
		if (cpt == 0)
		{
			//x = début, y = hauteur, z = largeur
			coordBox.x = *(histo + i);
			coordBox.z = size;
			boxcpt++;
		}
		if (*(histo + i + 1) == *(histo + i) + 1)
			cpt++;
		else
		{
			coordBox.y = cpt;
			box[boxcpt] = coordBox;
			cpt = 0;
		}	
		
	}
	*p = boxcpt;
}

void FindLines(SDL_Surface *img, Coord *box)
{
	Uint32 pixel;
	Uint8 r,g,b;

	for(int j = 0 ; j < img->h ; j++)
	{
		printf("%d\n",box[j].x);
		if (box[j].x == j)
		{
			j--;
			for(int i = 0; i < box[j].z; i++)
			{
				pixel = getpixel(img,i,j);
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, 255, 0, 0);
				putpixel(img, i, j, pixel);
			}
			j++;
		}

	}
}

                                                                            								                     

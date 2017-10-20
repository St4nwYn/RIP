#include <stdlib.h>
#include <stdio.h>
#include "pixel_operations.h"
#include "segmentation.h"


void Polish(SDL_Surface *img, int l)
{
	Uint32 pixel;
	Uint8 r,g,b;
	int end = (img -> h)-l;
	for(int i = 0; i < img-> w; i++)
	{
		for(int j = 0; j < end; j++)
		{			
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if (r == 255)
			{				
				int k = 1;
				int makeitblack = 0;
				while(k<l &&  k>=0)
				{
					pixel = getpixel(img,i,j+k);
					SDL_GetRGB(pixel, img->format, &r, &g, &b);
					if (makeitblack == 1)
					{	
						
						pixel = SDL_MapRGB(img->format, 0, 0, 0);
						putpixel(img, i, j+k, pixel);
						k--;
					}
					
					else
					{
						if (r != 255)
							makeitblack = 1;
							
						else
							k++;
					}	
						
				}
				
			}
		}
		
	}
}

void DefineBlocks(SDL_Surface *img)
{
}

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
			cpt++;			
		}	
	}
	*p = cpt;
}

void List2Struct(int *histo, Coord *box, int *p, int size)
{
	int cpt = 0, boxcpt = 0;
	Coord coordBox;
	for(int i = 0; i < *p; i++)
	{		
		if (cpt == 0)
		{
			//x = début, y = hauteur, z = largeur
			coordBox.x = *(histo + i);
			coordBox.z = size;	
		}
		
		if (*(histo + i + 1) == *(histo + i) + 1)
			cpt++;
		else
		{
			coordBox.y = cpt;
			box[boxcpt] = coordBox;
			boxcpt++;
			cpt = 0;			
		}	
		
	}
	*p = boxcpt;
}

void FindLines(SDL_Surface *img, Coord *box)
{
	Uint32 pixel;
	Uint8 r,g,b;
	int boxcpt = 0, up = 0;
	for(int j = 0 ; j < img->h ; j++)
	{
		if (box[boxcpt].x == j)
			up = 1;
			
		if (box[boxcpt].x + box[boxcpt].y == j || up == 1 )
		{			
			if (up == 1)
				j--;
			else
				j++;
				
			for(int i = 0; i < box[boxcpt].z; i++)
			{
				pixel = getpixel(img,i,j);
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, 255, 0, 0);
				putpixel(img, i, j, pixel);
			}
			
			if (up == 1)
				j++;
			else
			{
				j--;
				boxcpt++;
			}
			up = 0;
		}
	}
}
                                                        
void VHisto(SDL_Surface *img, int be, int h, int w, int *histo , int *p)
{
	Uint32 pixel;
	Uint8 r,g,b,average;
	int sum, cpt = 0;
	for(int i = be; i < be + w ; i++)
	{
		sum = 0;
		for(int j = be ; j < be + h ; j++)
		{
		
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			sum+=r;
		}
		average = sum/w;		
		if (average!=255)
		{			
			*(histo + cpt) = i;
			cpt++;			
		}	
	}
	*p = cpt;
	for(int i = 0; i < *p ; i++)
	{
		printf("%d\n", histo[i]);
	}
}

/*void F(SDL_Surface *img, int *histoV, int x, int y, int z, int *p)
{
    Uint32 pixel;
	Uint8 r,g,b;
	int cpt = 0;
	for(int j = x ; j < z ; j++)
	{
		
		if (cpt = 0)
		{
			for(int i = histo[]; i < histo [0] + y; i++)
			{
				pixel = getpixel(img,i,j);
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, 255, 0, 0);
				putpixel(img, i, j, pixel);
			}
		}
		if(histo[i] + 1 == histo[i+1])
		{					
			for(int i = 0; i < y; i++)
			{
				pixel = getpixel(img,i,j);
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, 255, 0, 0);
				putpixel(img, i, j, pixel);
			}
		}
	}	
}*/

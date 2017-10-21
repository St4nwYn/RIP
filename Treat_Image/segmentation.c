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

void ToEvery(funct_t fonct, Coord *box, int end)
{
	for(int i = 0; i < end; i++)
		fonct(box[i]);
}

int HHisto(SDL_Surface *img, Coord *histo, Coord box, int p)
{   
	Uint32 pixel;
	Uint8 r,g,b,average;
	int sum;
	int bx = box.x, bxl = box.x + box.w;
	
	for(int j = box.y; j < box.h+box.y ; j++)
	{
		sum = 0;
		for( int i = bx; i < bxl  ; i++)
		{
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			sum+=r;	
		}
		average = sum/box.w ;
		
		if (average!=255)
		{	
			histo[p].x = box.x;
			histo[p].y = j;
			histo[p].w = box.w;
			histo[p].h = 1;
			p++;
		}
	}
	
	return p;
}

int List2StructLine(Coord *histo, Coord *box, int p)
{
	int cpt = 0, boxcpt = 0;
	Coord coordBox;
	for(int i = 0; i < p; i++)
	{		
		
		if (cpt == 0)
		{
			coordBox.y = histo[i].y;
			coordBox.x = histo[i].x;
			coordBox.w = histo[i].w; 
			
		}
		if (histo[i+1].y == histo[i].y + 1)
			cpt++;
		else
		{
			coordBox.h = cpt;
			box[boxcpt] = coordBox;
			
			boxcpt++;
			cpt = 0;			
		}	
		
		
	}	
		
	return boxcpt;
}

void Print(SDL_Surface *img, Coord box)
{
	Uint32 pixel;		
	Uint8 r,g,b;
	if(box.x> 0) 
	{
		box.x--;
		if (box.x + box.w < img->w)
			box.w+=2;
		else
			box.w++;
	}
	else if (box.x + box.w < img->w)
		box.w++;
	
	if(box.y>0)
	{
		box.y--;
		if (box.y + box.h < img->h)
			box.h+=2;
		else
			box.w++;
	}
	else if (box.y + box.h < img -> h)
		box.h++;
	
	int i = box.x, j = box.y;
	for(; j < box.y + box.h ; j++)
	{
		pixel = getpixel(img,i,j);
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		pixel = SDL_MapRGB(img->format, 255, 0, 0);
		putpixel(img, i, j, pixel);
	}
	
	for(; i < box.x + box.w; i++)
	{
		pixel = getpixel(img,i,j);
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		pixel = SDL_MapRGB(img->format, 255, 0, 0);
		putpixel(img, i, j, pixel);
	}
	
	for(; j > box.y -1 ; j--)
	{
		pixel = getpixel(img,i,j);
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		pixel = SDL_MapRGB(img->format, 255, 0, 0);
		putpixel(img, i, j, pixel);
	}
		
	for(; i > box.x-1; i--)
	{
		pixel = getpixel(img,i,j);
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		pixel = SDL_MapRGB(img->format, 255, 0, 0);
		putpixel(img, i, j, pixel);
	}
}
                                            
int VHisto(SDL_Surface *img, Coord *histo , Coord box, int p)
{
	Uint32 pixel;
	Uint8 r,g,b,average;
	int sum;
	for(int i = box.x; i < box.x + box.w ; i++)
	{
		
		sum = 0;
		for(int j = box.y ; j < box.y + box.h ; j++)
		{		
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			sum+=r;
		}
		average = sum/ box.h;		
		if (average!=255)
		{	
			histo[p].y = box.y;
			histo[p].h = box.h;
			histo[p].x = i;		
			histo[p].w = 1;
			p++;			
		}	
	}


	return p;
}

int List2StructChar(Coord *histo, Coord *box, int p)
{
	int cpt = 0, boxcpt = 0;
	Coord coordBox;
	for(int i = 0; i < p; i++)
	{				
		if (cpt == 0)
		{
			coordBox.y = histo[i].y;
			coordBox.x = histo[i].x;
			coordBox.h = histo[i].h; 
			
		}
		if (histo[i+1].x == histo[i].x + 1)
			cpt++;
		else
		{
			coordBox.w = cpt;
			box[boxcpt] = coordBox;
			boxcpt++;
			cpt = 0;			
		}	
	}
	
	//for (int i = 0; i < 100 ; i++)
	//{
	//	printf("(x,y,w,h) = (%d,%d,%d,%d)\n", box[i].x, box[i].y, box[i].w, box[i].h);
	//}
	
	//printf("%d\n",boxcpt);
	return boxcpt;
}	
	

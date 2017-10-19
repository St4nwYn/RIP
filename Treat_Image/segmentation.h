// segmentation.h
 
# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_
 
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>

typedef struct Coord Coord;
struct Coord 
{
	int x;
	int y;
};
/*
 * Coord coordonnees;
 * coordonnees.x = 7; 
 */
 
Uint8 HHisto(SDL_Surface *img, int begin, int h, int w, Uint8 histo[]);
void FindLines(SDL_Surface *img, Uint8 histo[]);

#endif

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
	int z;
};
/*
 * Coord coordonnees;
 * coordonnees.x = 7; 
 */
 
void HHisto(SDL_Surface *img, int be, int h, int w, int *histo, int *p);
void FindLines(SDL_Surface *img, Coord *box);
void List2Struct(int *histo, Coord *box, int *p, int size);
#endif

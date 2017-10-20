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

typedef struct CoordBlock CoordBlock;
struct CoordBlock
{
	int x;
	int y;
	int w;
	int h;
	int* nextBlock;
}
/*
 * Coord coordonnees;
 * coordonnees.x = 7; 
 */
void Polish(SDL_Surface *img, int l);
void HHisto(SDL_Surface *img, int be, int h, int w, int *histo, int *p);
void FindLines(SDL_Surface *img, Coord *box);
void List2Struct(int *histo, Coord *box, int *p, int size);
void VHisto(SDL_Surface *img, int be, int h, int w, int *histo , int *p);
//void F(SDL_Surface *img, int *histoV, int x, int y, int z, int *p);
#endif

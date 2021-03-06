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
	//coord
	int x;
	int y;
	//size
	int w;
	int h;
};

void Polish(SDL_Surface *img, int l, int *leftM, int *rightM);
void PolishH(SDL_Surface *img, int l, int *leftM, int *rightM);
int HHisto(SDL_Surface *img, Coord *histo, Coord box,int p);
int List2StructLine(Coord *histo, Coord *box, int p);
void Print(SDL_Surface *img, Coord box);
int VHisto(SDL_Surface *img, Coord *histo, Coord box , int p);
int List2StructChar(Coord *histo, Coord *box, int p);

#endif

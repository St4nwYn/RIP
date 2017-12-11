// treat_image.h
 
# ifndef TREAT_IMAGE_H_
# define TREAT_IMAGE_H_
 
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
#include "Matrix.h"
void wait_for_keypressed(void);
struct Matrix *rogne(struct Matrix *mat)
struct Matrix *applysklt(struct Matrix *mat)
struct Matrix *sklt(struct Matrix *mat)
SDL_Surface* Load_Image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void ToGrayScale(SDL_Surface *img);
void Binarize(SDL_Surface* img);

#endif

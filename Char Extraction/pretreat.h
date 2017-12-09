// segmentation.h
 
# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

void ToGrayScale(SDL_Surface *img);
void Binarize(SDL_Surface* img);

#endif

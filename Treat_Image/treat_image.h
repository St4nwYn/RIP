// treat_image.h
 
# ifndef TREAT_IMAGE_H_
# define TREAT_IMAGE_H_
 
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>

void wait_for_keypressed(void);
SDL_Surface* Load_Image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void ToGrayScale(SDL_Surface *img);
void Binarize(SDL_Surface* img);

#endif

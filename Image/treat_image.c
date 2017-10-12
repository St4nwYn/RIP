#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

SDL_Surface* Load_Image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;

}

void ToGrayScale(SDL_Surface *img)
{
	Uint32 pixel;
	Uint8 r,g,b;
	unsigned long luminance;
	for(int i = 0;i<img->w;i++)
		for(int j = 0;j<img->h;j++)
		{
			pixel = getpixel(img,i,j);
			SDL_GetRGB(pixel,img->format, &r, &g, &b);
			luminance =  0.3*r + 0.59*g + 0.11*b;
			r = b = g = luminance;
			pixel = SDL_MapRGB(img->format,r,g,b);
			putpixel(img,i,j,pixel);
		}
}

void Binarize(SDL_Surface* img)
{
	Uint32 pixel;
	Uint8 r, g, b, bw;  
	Uint8 average;	
	for(unsigned int i = 0; i<(unsigned int)img->w; i++)
		for(unsigned int j = 0; j<(unsigned int)img->h; j++)
		{
			pixel = getpixel(img, i, j);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			average = (r + g + b)/3;
			if (average<128)
				bw = 0;
			else
				bw = 255;
			pixel = SDL_MapRGB(img->format, bw, bw, bw);
			putpixel(img, i, j, pixel);
		}
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	if (argc>2)
		errx(1,"Too many arguments given.");
	if (argc<2)
		errx(1,"Not enough arguments given.");
	SDL_Surface *img = Load_Image(argv[1]);
	ToGrayScale(img);
	Binarize(img);
	//Save image BMP format only
	SDL_SaveBMP(img,"modif.bmp");
	SDL_FreeSurface(img);
	SDL_Quit();
	return 0;
}

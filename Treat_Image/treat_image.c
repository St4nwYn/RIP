#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "treat_image.h"

#include "segmentation.h"
#include "pretreat.h"
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

struct Matrix *sklt(struct Matrix *mat)
{
  int o = 1;
  struct Matrix *ret = initMatrix(mat -> lines, mat -> cols,initList(mat -> lines, mat -> cols));
  for(size_t i =0; i<mat -> lines;i++)
    for(size_t j = 0; j<mat -> cols;j++)
      ret->values[i][j] = 1;
  for(size_t i = 0; i < mat -> lines; i++)
    {
      o = 1;
      for(size_t j = 0; j < mat -> cols; j++)
	{
	  if(j + 1 < mat -> lines && mat -> values[i][j+1] != 0)
	    o = 1;
	  if(mat -> values[i][j] == 0 && o == 1)
	    {
	      o = 0;
	      ret -> values[i][j] = 0;
	    }
	  if(mat -> values[i][j] != 0)
	    o = 1;
	}
    }
  return ret;
}
struct Matrix *applysklt(struct Matrix *mat)
{
  struct Matrix *ret = initMatrix(mat -> lines, mat -> cols,initList(mat -> lines, mat -> cols));
  for(size_t i =0; i<mat -> lines;i++)
    for(size_t j = 0; j<mat -> cols;j++)
      ret->values[i][j] = 1;
  int o = 0;
  for(size_t i = 0; i < mat -> lines; i++)
    {
      o = 0;
      for(size_t j = 0; j < mat -> cols; j++)
	{
	  if(mat -> values[i][j] == 0)
	    o = o==0;    
	  if(o == 1)
	    {
	      ret -> values[i][j] = 0;
	    }
	}
    } 

  return ret;
}
struct Matrix *rogne(struct Matrix *mat)
{
  struct Matrix *ret = initMatrix(32, 16,initList(32,16));
  for(size_t i =0; i<32;i++)
    for(size_t j = 0; j<16;j++)
      ret->values[i][j] = 1;
    
  size_t initi;
  size_t endi;
  size_t initj;
  size_t endj;
  size_t r;
  size_t t;
  if (mat -> lines >= 32 && mat -> cols >= 16)
    {
      initi = 0;
      endi = mat -> lines;
      initj = 0;
      endj = mat -> cols;
      r = (32 - mat -> lines)/2;
      t = (24 - mat -> cols)/2;
      for(size_t i = initi; i < endi && r < 32; i++, r++)
	{
	  t = 0; 
	  for(size_t j = initj; j < endj && t < 16; j++, t++)
	ret -> values[r][t] = mat -> values[i][j];
	}
    }
  else if(mat -> lines < 32)
    {
      r = (32 - mat -> lines)/2;
      t = (16 - mat -> cols)/2;
      initi = 0;
      endi = mat -> lines;
      initj = 0;
      endj = mat -> cols;
      for(size_t i = initi; i < endi && r < 32; i++, r++)
	{
	  t = (16 - mat -> cols)/2;
	  for(size_t j = initj; j < endj && t < 16; j++, t++)
	    ret -> values[r][t] = mat -> values[i][j];
	}
    }
  else
    {
      r = (32 - mat -> lines)/2;
      t = (16 - mat -> cols)/2;
      initi = 0;
      endi = mat -> lines;
      initj = 0;
      endj = mat -> cols;
      for(size_t i = initi; i < endi && r < 32; i++, r++)
	{
	  t = (16 - mat -> cols)/2; 
	  for(size_t j = initj; j < endj && t < 16; j++, t++)
	    {
	      ret -> values[r][t] = mat -> values[i][j];
	    }
	}
    }
  return ret;
}

int main(int argc, char* argv[])                                                
{
	//First = check the entry    
	SDL_Init(SDL_INIT_VIDEO);                                                   
	 if (argc>2)                    
		 errx(1,"Too many arguments given.");
	 if (argc<2) 
	  	 errx(1,"Not enough arguments given.");                             
	 
	 SDL_Surface *img;
	 //Pretreat
	 img = Load_Image(argv[1]);	 
	 ToGrayScale(img);
	 Binarize(img);
	 SDL_SaveBMP(img,"binarize.bmp");
	 SDL_FreeSurface(img);  
	 
	 //Lissage
	 
	 int *margeD = calloc(1,sizeof(int));
	 int *margeG = calloc(1,sizeof(int));
	 *margeD = 0;
	 *margeG = 0;
	 img = Load_Image("binarize.bmp");
	 Polish(img, 30,margeG,margeD);
	 PolishH(img, 30,margeG,margeD);	 
	 //display_image(img);
	 /*
	 //Rect
	 Coord *box = calloc(img -> h, sizeof(Coord));
	 box[0].x = 0;
	 box[0].y = 0;
	 box[0].w = (img -> w);
	 box[0].h = (img -> h);
	 
	 
	 //LineBlocks
	 Coord *histo = calloc(img -> h, sizeof(Coord));
	 int p = 0;
	 //for every;
	 p = HHisto(img,histo,box[0],p);
	 
	 
	 //remettre à 0 coords.
	 p = List2StructLine(histo,box,p);
	 
	 
	 free(histo);
	 histo = calloc((img -> w) * (img -> h), sizeof(Coord));
	 int p2 = 0;
	 
	 for (int i = 0; i < p; i++)
	 {
		 p2 = VHisto(img,histo,box[i],p2);
		 //printf("(x,y,w,h,p) = (%d,%d,%d,%d,%d)\n", histo[i].x, histo[i].y, histo[i].w, histo[i].h,i);
	 }
	 printf("%d\n",p2);
	 p = 0;
	 box = calloc((img -> h) * (img -> w), sizeof(Coord));
	 p2 = List2StructChar(histo,box,p2); 
	 
	 for (int i = 0; i < p2; i++)
		Print(img,box[i]); 	 
	
	 free(histo);
	 free(box);*/
	 SDL_SaveBMP(img,"modif.bmp");
	 SDL_FreeSurface(img);
	 SDL_Quit();                         
	 return 0; 
}  

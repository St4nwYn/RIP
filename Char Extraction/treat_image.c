#include "treat_image.h"
#include "segmentation.h"
#include "pretreat.h"
#include "pixel_operations.h"
#include "Matrix.h"

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

  if ( screen == NULL )
  {
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
      printf("PERFECT\n");
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
      printf("PERF\n");
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
      printf("FECT\n");
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
/*
struct Matrix *rognMatrix(struct Matrix *mat)
{
  size_t lines = mat->lines;
  size_t cols =mat->cols;
  size_t beginl = 0;
  size_t endl = mat->lines-1;
  int empty = 1;
  size_t i = 0,j;

  //vertical up
  while(empty && i<lines)
  {
    j=0;
    while(empty && j<cols)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      j++;
    }
    if (empty)
      beginl++;
    i++;
  }

  //vertical down
  i = lines-1;
  j = 0;
  empty = 1;
  while(empty && i!=0)
  {
    j=0;
    while(empty && j<cols)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      j++;
    }
    if (empty)
      endl--;
    i--;
  }

  if (empty)
  {
    j=0;
    while(empty && j<cols)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      j++;
    }
    if (empty)
      endl--;
      }
  
  //horizontal to right
  size_t beginc = 0, endc= cols-1;
  j = 0;
  empty = 1;
  while(empty && j<cols)
  {
    i=0;
    while(empty && i<lines)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      i++;
    }
    if (empty)
      beginc++;
    j++;
  }

  //horizontal to left
  j = cols-1;
  empty = 1;
  while(empty &&  j!=0)
  {
    i=0;
    while(empty && i<lines)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      i++;
    }
    if (empty)
      endc--;
    j--;
  }

  if(empty)
  {
    i=0;
    while(empty && i<lines)
    {
      if (mat->values[i][j] == 0)
	empty = 0;
      i++;
    }
    if (empty)
      endc--;
      }
  
  cols = endc-beginc;
  lines = endl-beginl;
  double **values = initList(lines, cols);
  for(size_t i = beginl; i<endl;i++)
    for(size_t j = beginc; j<endc;j++)
      values[i-beginl][j-beginc] = mat->values[i][j];
  return initMatrix(lines,cols,values);
  
}*/
/*
struct Matrix *extractChar(struct Matrix *mat)
{
  
  if (mat->cols>mat->lines)
  {
  }
  else
  {
  }
    
}
*/
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
	 //display_image(img);
	 ToGrayScale(img);
	 Binarize(img);
	 SDL_SaveBMP(img,"Binarized.bmp");
   
	 img = IMG_Load(argv[1]);
	 //Smooth
	 int *leftM = calloc(1,sizeof(int));
	 int *rightM = calloc(1,sizeof(int));
	 *leftM = 0;
	 *rightM = 0;
	 Polish(img, 30,leftM,rightM);
	 //display_image(img);
	 PolishH(img, 30,leftM,rightM);
	 //display_image(img);
	 SDL_SaveBMP(img,"Polished.bmp");
	 img = IMG_Load(argv[1]);

	 //Rect
	 Coord *box = calloc(img -> h, sizeof(Coord));
	 box[0].x = 0;
	 box[0].y = 0;
	 box[0].w = (img -> w);
	 box[0].h = (img -> h);


	 //LineBlocks
	 Coord *histo = calloc(img -> h, sizeof(Coord));
	 int p = 0;
	 	//Step1
	 p = HHisto(img,histo,box[0],p);
	 	//Step2
	 p = List2StructLine(histo,box,p);
	 for(int i = 0; i < p; i++)
	 	 Print(img,box[i]);
	 //display_image(img);
	 free(histo);
	 SDL_SaveBMP(img,"Lines.bmp");
	 img = IMG_Load(argv[1]);

	 //CharBlocks
	 histo = calloc((img -> w) * (img -> h), sizeof(Coord));
	 int p2 = 0;
  	 for (int i = 0; i < p; i++)
		 p2 = VHisto(img,histo,box[i],p2);
	 p = 0;
	 box = calloc((img -> h) * (img -> w), sizeof(Coord));
	 p2 = List2StructChar(histo,box,p2);
	 for(int i =0; i<p2;i++)
	   Print(img,box[i]);

	 for (size_t i = 0; i < (size_t)p2;i++)	   
	 {
	   printf("%u\n",i);
	   Uint32 pixel;
	   Uint8 r,g,b;
	   box[i].w++;
	   box[i].h++;
	   size_t lines = (size_t)(box[i].h);
	   size_t cols = (size_t)(box[i].w);
	   
	   printf("x = %d, y = %d, h = %d, w = %d\n\n",box[i].x,box[i].y,box[i].h,box[i].w);
	   struct Matrix *mat = initMatrix(lines,cols,initList(lines,cols));

	   for(size_t j = box[i].y;j<box[i].y+lines;j++)
	     for(size_t k = box[i].x;k<box[i].x+cols;k++)
	       {
		 pixel = getpixel(img,k,j);
		 SDL_GetRGB(pixel,img->format, &r, &g, &b);
		 if (r == 255)
		   mat->values[(size_t)(j-box[i].y)][(size_t)(k-box[i].x)] = 1;
		 else
		   mat->values[(size_t)(j-box[i].y)][(size_t)(k-box[i].x)] = 0;
	       }
	   mat = rogne(mat);
	   mat = sklt(mat);
	   mat = applysklt(mat);
	   printMatrix(mat);
	   printf("\n");
	   
	 }
	 //display_image(img);
	 //end
	 free(histo);
	 free(box);
	 SDL_SaveBMP(img,"Char.bmp");
	 SDL_FreeSurface(img);
	 SDL_Quit();
	 return 0;
}

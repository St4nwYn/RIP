## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= Save.o pixel_operations.o pretreat.o segmentation.o Matrix.o treat_image.o
DEP= ${SRC:.o=.d}
 
all: treat_image
 
treat_image: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} treat_image
 
-include ${DEP}
 
# END

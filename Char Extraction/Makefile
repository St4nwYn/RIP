## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
OBJ= pixel_operations.o pretreat.o segmentation.o treat_image.o Matrix.o
DEP= ${SRC:.o=.d}
 
all: treat_image
 
treat_image: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} treat_image
 
-include ${DEP}
 
# END

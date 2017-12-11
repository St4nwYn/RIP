#Makefile

CC= gcc
LD= $(CC)

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -std=c99 -Wall -Wextra -Werror
CFLAGS+= `pkg-config --cflags gtk+-3.0` -export-dynamic
LDFLAGS= `pkg-config --libs gtk+-3.0`
LDFLAGS+= `pkg-config --libs gmodule-2.0`
LDFLAGS+= `pkg-config --libs sdl` -lSDL_image

SRC= $(shell find src -type f -name "*.c")
OBJ= ../Treat_Image/pixel_operations.o ../Treat_Image/pretreat.o 
OBJ+= ../Treat_Image/treat_image.o ../Treat_Image/segmentation.o 
OBJ+= main.o
DEP= ${OBJ:.o=.d}

all: start
	        
start: ${OBJ}
	        $(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	        $(CC) -o $@ -c $< $(CFLAGS)
		                


.PHONY: clean

clean: 
	        rm -rf ${OBJ} -rf ${DEP}

# END


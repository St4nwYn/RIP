# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS = -lm

OBJ = NeuralNetwork.o Main.o
DEP = ${OBJ:.o=.d}

all: Main

Main: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ} ${DEP} Main

-include ${DEP}

# END

# Makefile
 
CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS = 
LDLIBS = -lm
 
OBJ = matrix.o NeuralClass.o
DEP = ${OBJ:.o=.d}
 
all: NeuralClass

NeuralClass: ${OBJ}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ} ${DEP} NeuralClass
 
-include ${DEP}
 
# END

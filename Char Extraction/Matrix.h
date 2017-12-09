#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdlib.h>
#include <stdio.h>

struct Matrix 
{
  double **values;
  size_t lines;
  size_t cols;
};

typedef double (*func_t)(double);

struct Matrix *initMatrix(size_t lines, size_t cols, double **values);
double **initList(size_t lines, size_t cols);
void printMatrix(struct Matrix *mat);
void freeMatrix(struct Matrix *mat);
struct Matrix *dotMatrix(struct Matrix *a, struct Matrix *b);
struct Matrix *applyMatrix(func_t f,struct Matrix *mat);
struct Matrix *hadamarMatrix(struct Matrix *a, struct Matrix *b);
struct Matrix *sumMatrix(struct Matrix *a, struct Matrix *b);
struct Matrix *transMatrix(struct Matrix *mat);

#endif

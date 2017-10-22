#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>
#include <stdio.h>

typedef double (*func_t)(double);

void transpose(double *mat, size_t lines, size_t cols, double *res);
void add(double *mat1, double *mat2, size_t L, size_t C, double *res);
void sub(double *mat1, double *mat2, size_t L, size_t C, double *res);
void hadamard(double *mat1, double *mat2, size_t L, size_t C, double *res);
void matriceApply(func_t f, double *mat, size_t matS, double *res);
void mul(double *m1, double *m2, size_t n, size_t m, size_t p, double *res);
double sum(double *mat, size_t matS);
void printMatrix(double *mat, size_t matL, size_t matS);
void concat(double *mat1, double *mat2, size_t S1, size_t S2, double *res);
void reshape(double *m, size_t L, size_t C, size_t nL, size_t nC, double *r);
void copy(double *mat, size_t S, double ret[]);;
#endif

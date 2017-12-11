#ifndef _SAVE_H_
#define _SAVE_H_

#include <stdio.h>
#include <stdlib.h>

char *tobin(double x);
double todec(char *bin);
void Mat2File(char *path, double **mat, size_t line, size_t cols);

double **File2Mat(char *path);
#endif

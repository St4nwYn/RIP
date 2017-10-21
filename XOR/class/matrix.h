/*
 * matrix.h: standard matrix operations
 *
 * 2017 Marwan Burelle / EPITA
 */
 
#ifndef _MATRIXSTDOPERATIONS_MATRIX_H_
#define _MATRIXSTDOPERATIONS_MATRIX_H_
 
#include <stdlib.h>

/*
 * transpose(mat, lines, cols, res)
 * transpose the lines X cols matrix mat into a cols X lines matrix
 * result will be stored in res
 */


void transpose(double mat[], size_t lines, size_t cols, double res[]);
 
/*
 * add(mat1, mat2, lines, cols, res)
 * computes res = mat1 + mat2
 * All 3 matrices have the form lines X cols
 */
void add(double mat1[], double mat2[], size_t lines, size_t cols, double res[]);
 
/*
 * mul(m1, m2, n, m, p, res)
 * computes res = m1 * m2
 * Where:
 *        m1 is a n X m matrix
 *        m2 is a m X p matrix
 *        res is a n X p matrix
 */

void sub(double mat1[], double mat2[], size_t lines, size_t cols, double res[]);
  
void hadamard(double mat1[], double mat2[], size_t lines, size_t cols, double res[]);
/*
 *
 *
 *Z[i][j] = X[i][j] * Y[i][j]
 *
 *
 *
 */

void kronecker(double mat1[], double mat2[], size_t lines, size_t cols, double res[]);
/*
 *
 *
 *Z[i][j] = X[0][i] * Y[j][0]
 *
 *
 *
 */

typedef double (*func_t)(double);

void matrice_apply(func_t f, double m[], size_t size, double res[]);

void hconcat(double mat1[], double mat2[], size_t lines, size_t cols1, size_t cols2, size_t colsr, double res[]);
/*
 *
 *
 *concatene 2 matrices du mm nb de lignes
 *
 *
 *
 */
void mul(double m1[], double m2[], size_t n, size_t m, size_t p, double res[]);
 
/*
 * print_matrix(mat, lines, cols)
 * prints the lines X cols matrix mat
 * All coeficient will be printed using the format " %4g ", line by line
 */

double sum(double m[], size_t len);

void print_matrix(double mat[], size_t lines, size_t cols);
 
#endif /* _MATRIXSTDOPERATIONS_MATRIX_H_ */

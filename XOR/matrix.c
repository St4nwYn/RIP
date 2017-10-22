
#include "matrix.h"

void transpose(double *mat, size_t matL, size_t matC, double *res)
{
	for (size_t i = 0; i < matL; i++)
		for (size_t j = 0; j < matC; j++)	
			res[i + j * matL] = mat[j + i * matC];
	
}

void add(double *mat1, double *mat2, size_t L, size_t C, double *res)
{
	for(size_t i = 0; i < L; i++)
		for(size_t j = 0; j < C; j++)
			res[j + i * C] = mat1[j + i * C]+ mat2[j + i * C];
}

void sub(double *mat1, double *mat2, size_t L, size_t C, double *res)
{
	for(size_t i = 0; i < L; i++)
		for(size_t j = 0; j < C; j++)
		{
			res[j + i * C] = mat1[j + i * C]- mat2[j + i * C];
		}
}

// Mult de 2 matrices de même taille
void hadamard(double *mat1, double *mat2, size_t L, size_t C, double *res)
{
  for(size_t i = 0; i < L; i++)
      for(size_t j = 0; j < C; j++)
		res[j + i*C] = mat1[j + i * C] * mat2[j + i * C];
    
}

void matriceApply(func_t f, double *mat, size_t matS, double *res)
{
  for(size_t i = 0; i < matS; i++)
      res[i] = f(mat[i]);
}

void mul(double *m1, double *m2, size_t n, size_t m, size_t p, double *res)
{
	for(size_t i = 0; i < n; i++)
		for(size_t j = 0; j < p; j++)
			res[j + i * p] = 0;
   
	for(size_t i = 0; i < n; i++)
		for(size_t j = 0; j < p; j++)
			for(size_t k = 0; k < m; k++)
				res[j + i * p] += m1[k + i * m] * m2[j + k * p] ;
   
}

double sum(double *mat, size_t matS)
{
  double j = 0;
  for(size_t i = 0; i < matS; i++)
      j += mat[i];
  return j;
}
	      
void printMatrix(double *mat, size_t matL, size_t matC)
{
  for(size_t i = 0; i < matL; i++)
  {
	  for(size_t j = 0; j < matC; j++)
		printf("%10g",mat[j + i * matC]);
	  printf("\n");
  }
}

void concat(double *mat1, double *mat2, size_t S1, size_t S2, double *res)
{
	
	for (size_t i = 0; i< S1; i++)
		res[i] = mat1[i];
	
	for (size_t i = 0; i<S2; i++)
		res[i+S1] = mat2[i];
}

void reshape(double *m, size_t L, size_t C, size_t nL, size_t nC, double *ret)
{
	size_t k = 0;
	for (size_t j = 0; j < C ; j++)
		for (size_t i = 0; i < L ; i++)
		{
			ret[k] = m[j + i*C];
			k++;
		}
	transpose(ret,nC,nL,ret);

}

void copy(double *mat, size_t S, double ret[])
{
	for(size_t i = 0; i < S; i++)
		ret[i] = mat[i];
}

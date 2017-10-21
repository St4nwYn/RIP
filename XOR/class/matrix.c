#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "NeuralClass.h"
#include <time.h>

void transpose(double mat[], size_t lines, size_t cols, double res[])
{
  for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  res[i + j * lines] = mat[j + i * cols];
	}
    }
}

void add(double mat1[], double mat2[], size_t lines, size_t cols, double res[])
{
    for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  res[j + i * cols] = mat1[j + i * cols]+ mat2[j + i * cols];
	}
    }
}

void sub(double mat1[], double mat2[], size_t lines, size_t cols, double res[])
{
    for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  res[j + i * cols] = mat1[j + i * cols] - mat2[j + i * cols];
	}
    }
}
void hadamard(double mat1[], double mat2[], size_t lines, size_t cols, double res[])
{
  for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  res[j + i*cols] = mat1[j + i * cols] * mat2[j + i * cols];
	}
    }
}

void kronecker(double mat1[], double mat2[], size_t lines, size_t cols, double res[])
{
  for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  res[j + i * cols] = mat1[i] * mat2[j*lines];
	}
    }
}


void matrice_apply(func_t f, double m[], size_t size, double res[])
{
  for(size_t i = 0; i < size; i++)
    {
      res[i] = f(m[i]);
    }
}


void hconcat(double mat1[], double mat2[], size_t lines, size_t cols1, size_t cols2, size_t colsr, double res[])
{
  for(size_t i = 0; i < lines; i++)
    {
      size_t j = 0;
      for (; j < cols1; j++)
	{
	  res[j + i * colsr] = mat1[j + i * cols1];
	}
      for (size_t k = 0; k < cols2; k++)
	{
	  res[j + k + i * colsr] = mat2[k + i * cols2];
	}
    }
}

void mul(double m1[], double m2[], size_t n, size_t m, size_t p, double res[])
{
  for(size_t i = 0; i < n; i++)
    {
      for(size_t j = 0; j < p; j++)
	{
	  for(size_t k = 0; k < m; k++)
	    {
	      res[j + i * p] += m1[k + i * m] * m2[j + k * p] ;
	    }
	}
    }
}

double sum(double m[], size_t len)
{
  double j = 0;
  for(size_t i = 0; i < len; i++)
    {
      j += m[i];
    }
  return j;
}
	      
void print_matrix(double mat[], size_t lines, size_t cols)
{
  for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
	{
	  printf("%10g",mat[j + i * cols]);
	}
      printf("\n");
    }
}

/* int main() */
/* { */
/*   return 0; */
/* } */


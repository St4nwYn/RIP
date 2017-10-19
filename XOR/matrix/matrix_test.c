/*
 * matrix.c: standard matrix operations, very quick tests
 *
 * 2017 Marwan Burelle / EPITA
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#include "matrix.h"
 
/*
 * some matrices and their dimensions
 */
 
#define lines1 3
#define cols1  4
 
double m1[] = {
  1.0, 2.0, 3.0, 4.0,
  5.0, 6.0, 7.0, 8.0,
  9.0, 10.0, 11.0, 12.0
};
 
#define lines2 4
#define cols2  3
 
double m2[] = {
  1.0, 2.0, 3.0,
  4.0, 5.0, 6.0,
  7.0, 8.0, 9.0,
  10.0, 11.0, 12.0
};
 
#define lines3 3
#define cols3  3
double m3[] = {
  1, 2, 3,
  4, 5, 6,
  7, 8, 9
};
 
double id[] = {
  1.0, 0.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 0.0, 1.0
};

#define lines4 2
#define cols4  5
double m4[] = {
  1.0, 2.0, 3.0, 4.0, 5.0,
  6.0, 7.0, 8.0, 9.0, 10.0
};

#define lines5 4
#define cols5  5

double m5[] = {
  1.0,  2.0,  3.0,  4.0,  5.0,
  6.0,  7.0,  8.0,  9.0,  10.0,
  11.0, 12.0, 13.0, 14.0, 15.0,
  16.0, 17.0, 18.0, 19.0, 20.0
};
/*
 * some empty matrices with correct dimensions for results
 */
 
/*
 * lines1 X cols1 or cols1 X lines1 matrix
 */
double res1[ lines1 * cols1 ];
 
/*
 * lines1 X cols2 matrix (for m1 * m2 results, or m3 * m3 or m3 * id)
 */
double res2[ lines1 * cols2 ];

/*
 * lines2 X cols2 matrix (for m2²)
 */
double res22[ lines2 * cols2 ];
/**/
double res3[ cols4 * lines5 ];
/**/
double res4[ lines1 * (cols1 + cols3)];
 
int main()
{
  /**/
  printf("m1 =\n");
  print_matrix(m1, lines1, cols1);
  transpose(m1,lines1,cols1, res2);
  printf("trans =\n");
  print_matrix(res2, lines2, cols2);
  /**/
  printf("m1 =\n");
  print_matrix(m1, lines1, cols1);
  add(m1,m1,lines1,cols1, res1);
  printf("add =\n");
  print_matrix(res1, lines1, cols1);
  /**/
  printf("m3 =\n");
  print_matrix(m3, lines3, cols3);
  mul(m3,m3,lines3,cols3,cols3, res2);
  printf("mul =\n");
  print_matrix(res2, lines3, cols3);
  /**/
  printf("\nm2 =\n");
  print_matrix(m2, lines2, cols2);
  hadamard(m2,m2,lines2,cols2,res22);
  printf("m2² = \n");
  print_matrix(res22, lines2, cols2);
  /**/
  printf("\n m4 =\n");
  print_matrix(m4, lines4, cols4);
  printf("\n m5 =\n");
  print_matrix(m5, lines5, cols5);
  kronecker(m4, m5, cols4, lines5, res3);
  printf("yaaay? = \n");
  print_matrix(res3, cols4, lines5);
  /**/
  printf("\n m1 =\n");
  print_matrix(m1, lines1, cols1);
  printf("\n m3 =\n");
  print_matrix(m3, lines3, cols3);
  hconcat(m1, m3, lines1, cols1, cols3, cols1 + cols3, res4);
  printf("yaaay? = \n");
  print_matrix(res4, lines1, cols1 + cols3);
  /**/
 
  /* TEST YOUR OPERATIONS HERE */
 
  return 0;
}

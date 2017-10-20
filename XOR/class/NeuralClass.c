#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "NeuralClass.h"
#include <math.h>


double sigmoid(double z)
{
  return 1/(1+exp(-z));
}

void forward(layer layers, double X[]) //X de taille 8 (1.1,0.0,1.0,0.1)
{
  double Z2[16];
  double A2[16];
  double Z3[4]; // 1 par 4
  double YHAT[4];
  mul(X, layers.W1, 4, 2 , 4 , Z2);
  //matrice_apply(sigmoid, Z2, 16, A2);
  //mul(A2, layers.W2, 4, 4, 1, Z3);
  //matrice_apply(sigmoid, Z3, 4, YHAT);
  }


/*
double treshold(layer layers, double X[])
{
  forward(layers, X);
}
*/
int main()
{
  double X[] = {
    0.0, 0.0,
    0.0, 1.0,
    1.0, 0.0,
    1.0, 1.0
  };
  layer neuron;
  forward(neuron,X);
  return 0;
}

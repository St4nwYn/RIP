#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "NeuralClass.h"
#include <time.h>
#include <math.h>

double W1[8]; // 2 par 4
double W2[4]; // 4 par 1


/*double  W1[] = {
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0
  };

double W2[] = {
    1.0,
    1.0,
    1.0,
    1.0
    };*/
double Y[4]; // 4 par 1 resultats attendu
double Z2[16];// 4 par 4
double A2[16];
double Z3[4]; // 1 par 4
double YHAT[4];
double COST[4]; 
double MINUSCOST[4]; // 1 par 4
double Z3PRIME[4];
double DELTA3[4]; // 4 par 1
double TRANSPOSE_A2[16];
double DJDW2[4]; //4 par 1
double TRANSPOSE_W2[4]; // 1 par 4
double DELTA3_TW2[16]; // 4 par 4
double Z2PRIME[16];
double DELTA2[16];
double TRANSPOSE_X[8]; // 2 par 4
double DJDW1[8]; // 2 par 4
double J[4]; // 4 par 1

double sigmoid(double z)
{
  return 1/(1+exp(-z));
}
double sigmoidprime(double z)
{
  return exp(-z)/((1+pow(exp(-z),2)));
}

double opposite(double z)
{
  return -z;
}

void costFunctionPrime(double X[],double Y[])
{
  //mul(-(Y-YHAT),matrice_apply(sigmoidprime, Z3))
  // forward(X);
  sub(Y, YHAT, 4, 1, COST);
  matrice_apply(opposite, COST, 4, MINUSCOST);
  matrice_apply(sigmoidprime, Z3, 4, Z3PRIME);
  hadamard(MINUSCOST, Z3PRIME, 4, 1, DELTA3);
  //mul(transpose(A2), DELTA3)
  transpose(A2, 4, 4, TRANSPOSE_A2);
  mul(TRANSPOSE_A2, DELTA3, 1, 4, 4, DJDW2);
  //mul(mul(delta3,transpose w2),matrice_apply(sigmoidprime, z2))
  transpose(W2, 4, 1, TRANSPOSE_W2);
  mul(DELTA3, TRANSPOSE_W2, 4, 1, 4, DELTA3_TW2);
  matrice_apply(sigmoidprime, Z2, 16, Z2PRIME);
  mul(DELTA3_TW2, Z2PRIME, 4, 4, 4, DELTA2);// soit mul soit hadamard
  //mul(transpose(x),delta2)
  transpose(X, 4, 2, TRANSPOSE_X);
  mul(TRANSPOSE_X, DELTA2, 2, 4, 4, DJDW1);
}

double costFunction(double X[], double Y[])
{
  //forward(X);
  sub(Y,YHAT, 4, 1, J);
  printf("\n");
  hadamard(J, J, 4, 1, J);
  double V = 0.5*sum(J, 4);
  return V;
}

void initW(double W[], size_t size)
{
  srand (time (NULL));
  for(size_t i = 0; i < size; i++)
    {
      W[i] = (double)rand()/RAND_MAX*2.0-1.0;
    }
}

void forward(double X[]) //X de taille 8 (1.1,0.0,1.0,0.1)
{
  mul(X, W1, 4, 2 , 4 , Z2);
  matrice_apply(sigmoid, Z2, 16, A2);
  mul(A2,W2, 4, 4, 1, Z3);
  matrice_apply(sigmoid, Z3, 4, YHAT);
}

double scalar(double z)
{
  return 3*z;
}

int main()
{
  double X[] = {
    0.0, 0.0,
    0.0, 1.0,
    1.0, 0.0,
    1.0, 1.0
  };

  double Y[] = {
    0.0,
    1.0,
    1.0,
    0.0
  };
 
  initW(W1, 8);
  initW(W2, 4);

  int k = 0;  
  //forward(X);
  double cost;// = costFunction(X,Y);
  while (k<10)
  {
    forward(X);
    cost = costFunction(X,Y);
    costFunctionPrime(X,Y);

    printf("\n YHAT = \n");
    print_matrix(YHAT,4,1);  
    printf("\ncost = %lf\n",cost);
    printf("\n W1 = \n");
    print_matrix(W1,2,4);
    printf("\n DJDW1 = \n");
    print_matrix(DJDW1,2,4);
    printf("\n W2 = \n");
    print_matrix(W2,4,1);
    printf("\n DJDW2 = \n");
    print_matrix(DJDW2,4,1);
    
    matrice_apply(scalar, DJDW1, 8, DJDW1);
    matrice_apply(scalar, DJDW2, 4, DJDW2);
    for(int i = 0; i < 4; i++)
      {
	if(DJDW2[i] <= -0.01 || DJDW2[i] >= 0.01)
	  W2[i] -= DJDW2[i];
      }
    for(int i = 0; i < 8; i++)
      {
	if (DJDW1[i]<= -0.01 || DJDW1[i]>= 0.01)
	  W1[i]-=DJDW1[i];
      }
    k++;
  }
  printf("\n Y = \n");
  print_matrix(Y,4,1);
  printf("\n YHAT = \n");
  print_matrix(YHAT,4,1);
  
  /*
  costFunctionPrime(X,Y);
  for(size_t i = 0; i < 8; i++)
    {
      matrice_apply(scalar, DJDW1, 8, DJDW1);
      if(DJDW1[i] <= 0.01)
	{
	  sub(W1,DJDW1, 2, 4, W1);
	}
      else if(DJDW1[i] > 0.01)
	{
	  sub(W1,DJDW1, 2, 4, W1);
	}
    }
  for(size_t j = 0; j < 4; j++)
    {
      matrice_apply(scalar, DJDW2, 4, DJDW2);
      if(DJDW2[j] <= 0.01)
	{
	  sub(W2,DJDW2, 4, 1, W2);
	}
      else if(DJDW2[j] > 0.01)
	{
	  sub(W2,DJDW2, 4, 1, W2);
	}
    }
  printf("cost : %lf \n",costFunction(X,Y));
  costFunctionPrime(X,Y);
  forward(X);
  printf("cost : %lf \n",costFunction(X,Y));
  
  
  printf("W1 : \n");
  print_matrix(neuron.W1, 2, 4);
  printf("W2 : \n");
  print_matrix(neuron.W2, 4, 1);
  
  //learn(neuron, neuron.W1, neuron.W2);
  
  printf("W1 : \n");
  print_matrix(neuron.W1, 2, 4);
  printf("W2 : \n");
  print_matrix(neuron.W2, 4, 1);
  printf("Z2 : \n");
  print_matrix(Z2, 4, 4);
  printf("A2 : \n");
  print_matrix(A2, 4, 4);
  printf("Z3 : \n");
  print_matrix(Z3, 4, 1);
  printf("COST : \n");
  print_matrix(COST, 1, 4);*/
  /*printf("YHAT : \n");
  print_matrix(YHAT, 4, 1);
  printf("Y : \n");
  print_matrix(Y, 4, 1);
  */
  return 0;
}
//BACK PROPAGATION A FAIRE

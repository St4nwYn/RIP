#ifndef _NEURALCLASS_H_
#define _NEURALCLASS_H_

#include <math.h>
#include <time.h>

double scalarize(double z);
double sigmoid(double z);
double sigmoidPrime(double z);
void initRandom(double *W, size_t WS, double min, double max);
void forward(double *X);
double costFunction(double *X,double *Y);
void costFunctionPrime(double *X, double *Y);
void setParams(double *params);
void getParams(double *params);
void computeNumGradient(double *X, double *Y);
void computeGradients(double *X,double *Y);
void costFunctionWrapper(double *params, double *X, double *Y);
void callBack(double *params);
void train(double *X, double *Y);


#endif

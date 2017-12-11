#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct Neuron
{
	double value, delta;
	double *weights;
	size_t nbw;
};

struct Network
{
	struct Neuron ***inputL, **hiddenL, ***EoutputL, ***outputL;
	size_t nbi,nbh,nbo;
	size_t nbex;
};

struct Network *initNetwork();
void freeNetwork(struct Network *NN);
void printNeuron(struct Neuron *N);
void printMatrix(struct Neuron ***N,size_t lines, size_t cols);
void initElm(struct Network *NN, char *output);
void initWeights(struct Network *NN, char *path, char mode);

int learning(struct Network *NN, double step);
void forward(struct Network *NN, size_t e);
#endif

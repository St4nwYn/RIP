#include "NeuralNetwork.h"


double randint()
{
	return (rand()/(double)RAND_MAX)*5;
}

struct Neuron *initNeuron(double val, size_t weights)
{
	struct Neuron *N = malloc(sizeof(struct Neuron));
	N->value = val;
	N->weights = calloc(weights,sizeof(double));
	N->delta = 0;
	N->nbw = weights;
	return N;
}

void freeNeuron(struct Neuron *N)
{
	free(N->weights);
	free(N);
}

struct Network *initNetwork(size_t nbex, size_t nbi, size_t nbh, size_t nbo)
{
	struct Network *NN = malloc(sizeof(struct Network));
	NN->inputL = calloc(nbex,sizeof(struct Neuron*));
	NN->EoutputL = calloc(nbex,sizeof(struct Neuron*));
	NN->outputL = calloc(nbex,sizeof(struct Neuron*));	
	
	for(size_t i = 0; i<nbex;i++)
	{
		NN->inputL[i]=calloc(nbi,sizeof(struct Neuron*));
		for(size_t j = 0; j<nbi;j++)
			NN->inputL[i][j] = initNeuron(0,nbh);
		NN->EoutputL[i]=calloc(nbo,sizeof(struct Neuron*));
		NN->outputL[i]=calloc(nbo,sizeof(struct Neuron*));
		for(size_t j = 0; j<nbo;j++)
		{
			NN->EoutputL[i][j] = initNeuron(0,0);
			NN->outputL[i][j] = initNeuron(0,0);
		}
	}
	NN->hiddenL = calloc(nbh,sizeof(struct Neuron*));
	for(size_t i = 0; i<nbh;i++)
		NN->hiddenL[i]=initNeuron(0,nbo);

	NN->nbi = nbi;
	NN->nbh = nbh;
	NN->nbo = nbo;
	NN->nbex = nbex;
	
	return NN;
}

void freeNetwork(struct Network *NN)
{
	for(size_t i = 0; i<NN->nbex;i++)
  {
		for(size_t j =0; j<NN->nbi;j++)
			freeNeuron(NN->inputL[i][j]);
    free(NN->inputL[i]);
		for(size_t j = 0; j<NN->nbo;j++)
		{
			freeNeuron(NN->EoutputL[i][j]);
			freeNeuron(NN->outputL[i][j]);
    }	
		free(NN->EoutputL[i]);
    free(NN->outputL[i]);
  }
	
	for(size_t i =0; i<NN->nbh;i++)
		freeNeuron(NN->hiddenL[i]);

	free(NN->inputL);
  free(NN->EoutputL);
  free(NN->outputL);
	free(NN->hiddenL);
	free(NN);
}

void printNeuron(struct Neuron *N)
{
	printf("value = %f\ndelta = %f",N->value,N->delta);
	printf("\n");
	if (N->nbw>0)
	{
		for(size_t i = 0;i<N->nbw;i++)
			printf("%f ",N->weights[i]);
		printf("\n");
	}
}

void printMatrix(struct Neuron ***N,size_t lines, size_t cols)
{
	for(size_t i = 0; i<lines;i++)
  {
    printf("Line[%u]\n",i);
    for(size_t j = 0; j<cols;j++)
    {
      printNeuron(N[i][j]);
      printf("\n");
    }
    printf("--------------------");
    printf("\n");
  }
  printf("\n");
}

double sigmoid(double x)
{
	return 1/(1+exp(-x));
}


void initElm(struct Network *NN)
{
	srand(time(NULL));
	//init input
	NN->inputL[1][1]->value = NN->inputL[2][0]->value = NN->inputL[3][0]->value = NN->inputL[3][1]->value = 1;
	
	for(size_t i = 0; i<NN->nbh;i++)
	{
    NN->inputL[0][0]->weights[i] = randint();
    NN->inputL[0][1]->weights[i] = randint();
	}

  for(size_t i = 1; i<NN->nbex;i++)
    for(size_t j = 0; j<NN->nbi;j++)
      NN->inputL[i][j]->weights = NN->inputL[0][j]->weights;
	
	//init expected output
	NN->EoutputL[1][0]->value = NN->EoutputL[2][0]->value = 1;
	
	//init hidden
	for(size_t i = 0; i<NN->nbh;i++)
		for(size_t j = 0; j<NN->nbo;j++)
    	NN->hiddenL[i]->weights[j] = randint();	
}

void forward(struct Network *NN, size_t e)
{
	struct Neuron *cur;
	struct Neuron *prev;
	for(size_t i =0; i<NN->nbh;i++)
	{
		cur = NN->hiddenL[i];
		for(size_t j=0; j<NN->nbi;j++)
		{
			prev = NN->inputL[e][j];
			cur->value += prev->weights[i]*prev->value; 
		}
		cur->value = sigmoid(cur->value);
	}
	
	for(size_t i =0; i<NN->nbo;i++)
  { 	
    cur = NN->outputL[e][i];
    for(size_t j=0; j<NN->nbh;j++)
    {
      prev = NN->hiddenL[j];
      cur->value += prev->weights[i]*prev->value;
    }
    cur->value = sigmoid(cur->value);
	}
}

void backward(struct Network *NN, size_t e)
{
	struct Neuron *cur;
	struct Neuron *prev;
	double sum = 0;
	
	for(size_t i =0; i<NN->nbo;i++)
	{
		cur = NN->outputL[e][i];
		prev = NN->EoutputL[e][i];
		cur->delta = prev->value - cur->value;
	}	

	for(size_t i =0 ; i<NN->nbh;i++)
	{
		cur = NN->hiddenL[i];
		sum =0;
		for(size_t j =0; j<NN->nbo;j++)
		{
			prev = NN->outputL[e][j];
			sum += cur->weights[j]*prev->delta;
		}
		cur->delta = cur->value * (1-cur->value) * sum;
	}
	
	for(size_t i =0 ; i<NN->nbi;i++)
  {
    cur = NN->inputL[e][i];
    sum =0;
    for(size_t j =0; j<NN->nbh;j++)
    {
      prev = NN->hiddenL[j];
      sum += cur->weights[j]*prev->delta;
    }
    cur->delta = cur->value * (1-cur->value) * sum;
  } 

}

void wUpdate(struct Network *NN, double step,size_t e)
{
	struct Neuron *cur;
	struct Neuron *prev;

	for(size_t i =0;i<NN->nbi;i++)
	{
		cur = NN->inputL[e][i];
		for(size_t j =0; j<NN->nbh;j++)
		{
			prev = NN->hiddenL[j];
			cur->weights[j] += step*cur->value*prev->delta;
		}
	}
	
	for(size_t i=0;i<NN->nbh;i++)
	{
		cur = NN->hiddenL[i];
		for(size_t j=0; j<NN->nbo;j++)
		{
			prev = NN->outputL[e][j];
			cur->weights[j] += step*cur->value*prev->delta;
		}
	}
}

double diffOutput(struct Network *NN)
{
	double sum = 0;
	for(size_t i= 0;i<NN->nbex;i++)
		for(size_t j=0;j<NN->nbo;j++)
			sum+= abs(NN->outputL[i][j]->delta);
			
	return sum;
}

void learning(struct Network *NN, double step)
{
	int k = 0;
	double diff;
	do
	{
		for(size_t e = 0; e<NN->nbex;e++)
		{
			forward(NN,e);
			backward(NN,e);
			wUpdate(NN,step,e);
			forward(NN,e);
		}
		k++;
	//	diff = diffOutput(NN);
	}
	while(k<50000);
}

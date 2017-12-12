#include <string.h>
#include "NeuralNetwork.h"
#include "Save.h"

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

//init input output alea w
void initElm(struct Network *NN, char* path)
{
  srand(time(NULL));
  
	//init inputs & outputs
	size_t len = strlen(path);
	//char in[len+12];	
	char *in = calloc(len+10,sizeof(char));
	strcat(in,path);
	strcat(in,"input.txt");
  double **input = File2Mat(in);
	free(in);
	
	char *out = calloc(len+11,sizeof(char));          
  strcat(out,path);
  strcat(out,"output.txt");

	double **output = File2Mat(out);
	free(out);
	for (size_t i = 0; i<NN->nbex;i++)
	{
		for(size_t j = 0; j<NN->nbi;j++)
			NN->inputL[i][j]->value= input[i][j];
		for(size_t j = 0; j<NN->nbo;j++)
			NN->EoutputL[i][j]->value = output[i][j];
	}
}
void initWeights(struct Network *NN, char *path, char mode)
{
  if (mode == 'r')
    {
      size_t len = strlen(path);
      char *file = calloc(len+10,sizeof(char));
      char *nb = calloc(3,sizeof(char)); 
      strcat(file,path);
      //strcat(file,"In.txt");
      //file[len+2] = '\0';
      for(size_t i =0; i<NN->nbi;i++)
	{
	  sprintf(nb,"%u", i + 1);
	  strcat(file,"I");
	  strcat(file,nb);
	  strcat(file,".txt");
	  NN->inputL[0][i]->weights=File2Mat(file)[0];
	  for(size_t j = len; j < strlen(file); j++)
	    file[j] = '\0';
  	}
      //NN->inputL[0][1]->weights=File2Mat("xor/I2.txt")[0];
      
      for(size_t i =0; i<NN->nbh;i++)
	{
	  sprintf(nb,"%u", i + 1);
	  strcat(file,"H");
	  strcat(file,nb);
	  strcat(file,".txt");
	  NN->hiddenL[i]->weights=File2Mat(file)[0];
	  for(size_t j = len; j < strlen(file); j++)
	    file[j] = '\0';
  	}
      /* NN->hiddenL[0]->weights=File2Mat("xor/H1.txt")[0]; */
      /* NN->hiddenL[1]->weights=File2Mat("xor/H2.txt")[0]; */
      free(file); 
    }  
  else
    {
      for(size_t i = 0; i<NN->nbh;i++)
	{
	  NN->inputL[0][0]->weights[i] = randint();
	  NN->inputL[0][1]->weights[i] = randint();
	}
      for(size_t i = 0; i<NN->nbh;i++)
    	for(size_t j = 0; j<NN->nbo;j++)
	  NN->hiddenL[i]->weights[j] = randint();	
    }
  for(size_t i = 1; i<NN->nbex;i++)
    for(size_t j = 0; j<NN->nbi;j++)
      NN->inputL[i][j]->weights = NN->inputL[0][j]->weights;
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
  double delta;
  for(size_t i= 0;i<NN->nbex;i++)
    for(size_t j=0;j<NN->nbo;j++)
      {
	delta = NN->outputL[i][j]->delta;
	if (delta < 0)
	  delta = -delta;
	sum+= delta;
      }
  return sum;
}

int learning(struct Network *NN, double step)
{
  int k = 0;
  double diff;
  int t = 0;
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
      diff = diffOutput(NN);
      if(diff > 1.9) 
      	step = 1/diff - 0.4; 
      else if(diff > 1.5) 
       	step = 1/diff - 0.49; 
      else if(diff > 1) 
       	step = 1/diff - 0.5;
      else
	step = 0.49;
      /*if(k<30000)
	printf("I MAKE IT WORK SOMEHOW    %d \n",k);*/
      if(k>30000 && t == 0)
	{
	  return 0;
	}
    }
  while(diff>0.1);
  printf("iter = %d \n",k);
  return 1;
}

size_t higher(double *list, size_t size)
{
  size_t s = 0;
  double m = list[0];
  for(size_t i = 0; i < size; i++)
    {
      if(list[i] > m)
	{
	  m = list[i];
	  s = i;
	}
    }
  return s;
}

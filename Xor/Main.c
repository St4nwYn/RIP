#include "NeuralNetwork.h"
#include "Save.h"

double **list2mat(double *list)
{
  double **out = calloc(1, sizeof(double*));
  out[0] = list;
  return out;
}


void xor(char mode)
{
	struct Network *NN = initNetwork(4,2,2,1);
	initElm(NN, "xor/");
	initWeights(NN,"xor/",mode);



	int i =0;
	learning(NN,0.49);
  	//printf("\nNB OF CALLS : %d\n", i);
  	//printMatrix(NN->outputL,4,1); 
	while (learning(NN,0.49)!=1)
    	{
      	initElm(NN, "xor/");
      	i++;
    	}
  	printf("\nNB OF CALLS : %d\n", i);
  	printMatrix(NN->outputL,4,1);
		



	//printMatrix(NN->inputL,4,2);
	
	/*
	if (mode == 'r')
	{
		initElm(NN, "xor/");
		for(size_t e =0; e<4;e++)
    	forward(NN,e);
  	printMatrix(NN->outputL,4,1);
	}*/
}

int main()
{
	
  xor('w');
  return 0; 					
}

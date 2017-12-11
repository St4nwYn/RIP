#include "NeuralNetwork.h"
#include "Save.h"

double **list2mat(double *list)
{
	double **out = calloc(1, sizeof(double*));
	out[0] = list;
	return out;
}

void xor()
{
  struct Network *NN = initNetwork(4,2,2,1);
  initElm(NN);
  int i =0;
  while (learning(NN,0.49)!=1)
    {
      initElm(NN);
      i++;
    }
  printf("\nNB OF CALLS : %d\n", i);
	printMatrix(NN->outputL,4,1);  
	Mat2File("xor/I1.txt",list2mat(NN->inputL[0][0]->weights),1,NN->nbh);
	Mat2File("xor/I2.txt",list2mat(NN->inputL[0][1]->weights),1,NN->nbh);
	Mat2File("xor/H1.txt",list2mat(NN->hiddenL[0]->weights),1,NN->nbo);
	Mat2File("xor/H2.txt",list2mat(NN->hiddenL[1]->weights),1,NN->nbo);
	
}

int main()
{
	xor();
	return 0;
}

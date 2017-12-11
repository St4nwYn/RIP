#include "NeuralNetwork.h"

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
  
  /*
  for(size_t i = 0; i<NN->nbex;i++)
    for(size_t j =0; j<NN->nbo;j++)
    {
      if(NN->outputL[i][j]->value>=0.5)
        NN->outputL[i][j]->value =1;
      else
        NN->outputL[i][j]->value = 0;
  }*/
  printMatrix(NN->outputL,NN->nbex,NN->nbo);
  /*for(size_t i =0; i<NN->nbh;i++)
  {
    printNeuron(NN->hiddenL[i]);
    printf("\n");
  }*/
}

int main()
{
	xor();
	return 0;
}

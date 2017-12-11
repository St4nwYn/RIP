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
  for(size_t e =0; e<4;e++)
    forward(NN,e);
  printMatrix(NN->outputL,4,1);
}

int main()
{
  xor();
  return 0; 					
}

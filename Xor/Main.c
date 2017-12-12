#include <string.h>
#include "NeuralNetwork.h"
#include "Save.h"

double **list2mat(double *list)
{
	double **out = calloc(1, sizeof(double*));
	out[0] = list;
	return out;
}

void keepGoodW(struct Network *NN, char *path)
{
  size_t len = strlen(path);
  char *file = calloc(len+10,sizeof(char));
  char *nb = calloc(3,sizeof(char));
  strcat(file,path);
  for(size_t i = 0; i<NN->nbi;i++)
    {
      sprintf(nb,"%u", i + 1);
      strcat(file,"I");
      strcat(file,nb);
      strcat(file,".txt");
      Mat2File(file,list2mat(NN->inputL[0][i]->weights),1,NN->nbh);
      for(size_t j = len; j < strlen(file); j++)
	file[j] = '\0';
    }
  for(size_t i = 0; i<NN->nbh;i++)
    {
      sprintf(nb,"%u", i + 1);
      strcat(file,"H");
      strcat(file,nb);
      strcat(file,".txt");
      Mat2File(file,list2mat(NN->hiddenL[i]->weights),1,NN->nbo);
      for(size_t j = len; j < strlen(file); j++)
	file[j] = '\0';
    }
      
}


void xor(char mode)
{
  int i =0;
  struct Network *NN = initNetwork(4,2,2,1);
  initElm(NN,"xor/");
  initWeights(NN,"xor/",mode);
  if(mode == 'r')
    {
      for(size_t j = 0; j < NN -> nbex; j++ )
	forward(NN,j);
    }
  else
    {
      while (learning(NN,0.49)!=1)
	{
	  i++;
	  initWeights(NN,"xor/",mode);
	}
      keepGoodW(NN, "xor/");
    }
  printf("\nNB OF CALLS : %d\n", i);
  printMatrix(NN -> outputL, 4, 1);
}

void alphalearn()
{
	int i =0;
  struct Network *NN = initNetwork(52,768,100,52);
  initElm(NN,"learning/alpha");
  initWeights(NN,"learning/alpha",'w');
	while (learning(NN,0.49)!=1)
  {
    i++;
    initWeights(NN,"learning/alpha",'w');
  }
      keepGoodW(NN, "learning/alpha");
    
  printf("\nNB OF CALLS : %d\n", i);
  printMatrix(NN -> outputL, 52, 52);

}

int main()
{
	
  xor('w');
  return 0; 					
}





















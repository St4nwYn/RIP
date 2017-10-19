



 
struct Layers {
  /* nuber of inputs */
  int nbinputs; //2
  
  /*number of outputs*/
  int nboutputs; //2

  /*number of hidden layers*/
  int nbhidden; //2
  
  double W1[8]; //2 par 4
  double W2[4]; //4 par 1 ATTENTION ERREUR PROBABLE
};

typedef struct Layers layer;

void forward(layer layers, double X[]);//X de taille 8 (1.1,0.0,1.0,0.1) 4 par 2

double sigmoid(double z);

#include "NeuralClass.h"
#include "matrix.h"

double *W1;
double *W2;
double *Z2;
double *A2;
double *Z3;
double *X; 
double *yHat;
double *Y;
double *dJdW2;
double *dJdW1;
double *paramsIni;
double *numgrad;
double *grad;
double *cost;

double scalarize(double z)
{
	return 3 * z;	
}

double sigmoid(double z)
{
	return 1/(1+exp(-z));
}

double sigmoidPrime(double z)
{
	return (exp(-z)/pow((1+exp(-7)),2));
}

void initRandom(double *W, size_t WS, double min, double max)
{
	srand (time (NULL));
	for(size_t i = 0; i < WS; i ++)
		W[i] = (double)rand()/RAND_MAX*max-min;
}

void forward(double *X)
{
	mul(X,W1,4,2,2,Z2);
	matriceApply(sigmoid, Z2, 8, A2);
	mul(A2, W2,4,2,1,Z3);
	matriceApply(sigmoid,Z3,4,yHat);
	
}

double costFunction(double *X, double *Y)
{
	forward(X);
	double costdif[4]; //4*1
	sub(Y,yHat,4,1,costdif);
	hadamard(costdif, costdif,4,1,costdif);
	return 0.5 * sum(costdif,4);
}

void costFunctionPrime(double *X, double *Y)
{	
	double delta3[4]; //4*1
	double delta2[8]; //4*2
	double costtrans[4]; //4*1
	double Z3prime[4]; //4*1
	double trans_A2[8]; // 2*4
	double Z2prime[8]; // 2*4
	double trans_W2[2]; // 1*2
	double tW2D3[8]; //4*2
	double trans_X[8]; // 2*4
	forward(X);
	
	//Calcul dJdW2	
	sub(yHat,Y,4,1,costtrans);
	matriceApply(sigmoidPrime,Z3,4,Z3prime);
	hadamard(costtrans,Z3prime,4,1,delta3);
	transpose(A2,4,2,trans_A2);
	mul(trans_A2,delta3,2,4,1,dJdW2);	
	//Calculer dJdW1
	matriceApply(sigmoidPrime,Z2,8,Z2prime);
	transpose(W2,2,1,trans_W2);
	mul(delta3,trans_W2,4,1,2,tW2D3);
	
	mul(tW2D3,Z2prime,4,2,2,delta2);
	mul(trans_X,delta2,2,4,2,dJdW1);
	
}

void setParams(double *params)
{
	//FIXME for letters
	//double W1_start = 0;
	double W1_end = 4;
	double W2_end = 6;
	
	double using1[4];
	for (size_t i = 0; i < W1_end; i++)
		using1[i] = params[i];	
	
	double using2[2];
	for (size_t i = W1_end; i < W2_end; i++)
		using2[i] = params[i];
	
	reshape(using1,1,4,2,2,W1);
	reshape(using2,1,2,2,1,W2);
}

void getParams(double *params)
{
	concat(W1,W2,4,2,params);
}

void computeGradients(double *X,double *Y)
{
	costFunctionPrime(X,Y);
	concat(dJdW1,dJdW2,4,2,grad);
}

void computeNumGradient(double *X, double *Y)
{
	concat(W1,W2,4,2,paramsIni);
	double *perturb = calloc(6, sizeof(double));

	for (size_t i = 0; i < 8; i++)
		numgrad[i] = 0;
	double e = pow(10,-4);
	double calc[8];
	double loss1;
	double loss2;
	
	
	for (size_t i = 0; i < 8 ; i++)
	{
		perturb[i] = e;
		add(paramsIni,perturb,1,6,calc);
		setParams(calc);
		loss2 = costFunction(X,Y);
		
		sub(paramsIni,perturb,1,6,calc);
		sub(paramsIni,perturb,1,6,calc);
		setParams(calc);
		loss1 = costFunction(X,Y);
		
		numgrad[i] = (loss2-loss1) / (2*e);
		perturb[i] = 0;
	}
	
	setParams(paramsIni);
	free(perturb);
}

void costFunctionWrapper(double *params, double *X, double *Y)
{
	setParams(params);
	*cost = costFunction(X,Y);
	computeGradients(X,Y);	
}

void callBack(double *params)
{
	setParams(params);
	*cost += costFunction(X,Y);
}

void train(double *X,double *Y)
{
	double x[8];
	double y[4];
	double *j = calloc(8,sizeof(double));
	copy(X,8,x);
	copy(Y,4,y);
	double *params0 = calloc(6,sizeof(double));
	getParams(params0);
	//fixme minimize res =
	
	//setParams(res);
	//optiminzationResults = res;
	free(params0);
	free(j);
	
	
	
}

int main()
{
	//init (W1 -> entrée W2 -> sortie) les poids
	W1 = calloc(4,sizeof(double)); //2*2
	initRandom(W1,4,2,2);
	
	W2 = calloc(2,sizeof(double)); //2*1
	initRandom(W2,2,1,2);
	/*
	printf("\nW1 =\n");
	printMatrix(W1,2,2);
	printf("\nW2 =\n");
	printMatrix(W2,2,1);
	*/
	//init layout
	Z2 = calloc(8,sizeof(double)); // Z2 = X * W1 // 4 * 2
	A2 = calloc(8,sizeof(double)); // A2 = sigmoide(Z2) // 4 * 2
	Z3 = calloc(4,sizeof(double)); // Z3 = A2 * w2 // 4 * 1	
	
	//init entrée
	X = calloc(8,sizeof(double)); //4*2
	X[0] = X[1] = X[2] = X[5] = 0.0;
	X[3] = X[4] = X[6] = X[7] = 1.0;
	
	//init sorties (yHat obtenue, Y attendue)
	yHat = calloc(4,sizeof(double)); //yHat = sigmoide(Z3) // 4*1
	Y = calloc(4,sizeof(double)); // 4*1
	Y[0] = Y[3] = 0.0;
	Y[1] = Y[2] = 1.0;
	
	//init dérivées
	dJdW1 = calloc(4,sizeof(double)); //2*2
	dJdW2 = calloc(2,sizeof(double)); //2*1
	
	//init
	paramsIni = calloc(6,sizeof(double)); //1*6	
	numgrad = calloc(6,sizeof(double));
	grad = calloc(6,sizeof(double));
	cost = calloc(1,sizeof(double));
	
	//main
	forward(X);	
	
	//norm(grad-numgrad)/norm(grad+numgrad)
	//libération des pointeurs
	free(W1);
	free(W2);
	free(yHat);
	free(X);
	free(Z2);
	free(A2);
	free(Z3);
	free(Y);
	free(dJdW1);
	free(dJdW2);
	free(paramsIni);
	free(numgrad);
	free(grad);
	free(cost);
	return 0;
}

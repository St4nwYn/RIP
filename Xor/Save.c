#include <stdio.h>
#include <stdlib.h>

void Mat2File(char *path, double **mat, size_t lines, size_t cols)
{
	FILE *file;
	file = fopen(path, "w+");
	//fputs("CACA BOUDIN PIPI\n",file);
	
	for(size_t i=0; i<lines;i++)
	{
		for(size_t j=0;j<cols;j++)
			fprintf(file,"%f ",mat[i][j]);
		fputc('\n',file);
	}
	fclose(file);	
}

int main()
{
	double **test = calloc(5,sizeof(double*));
	for(size_t i = 0; i<5;i++)
		test[i] = calloc(2,sizeof(double));
	Mat2File("yop.txt",test,5,2);
	
	return 0;
}



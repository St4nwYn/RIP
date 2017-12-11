#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *tobin(double x)
{
	int neg = 0;
	int i = 0, j = 0;
	char *out = calloc(255,sizeof(char));
	char *ret = calloc(255,sizeof(char));

	if (x == 0 || x ==-0)
		return "0";
	
	if (x<0)
	{
		x=-x;
		neg = 1;
	}
		
	int y = (int)x;
	if(y == 0)
	{
		out[j] = '0';
		j++;
	} 	

	for(;y>0;y/=2,j++)
	{
		if(y%2==0)
			out[j] = '0';
		else
			out[j] = '1';
	}

	if(neg==1)
	{
		out[j]='2';
		j++;
	}
	
	for(;i<j;i++)
	  ret[i] = out[j-i-1];

//nb virgule
	x-=(int)x;
	if(y!=x)
	{ 
		ret[j]=',';
		j++;
		for(i = 0;i<6 && x!=0;j++,i++)
		{
			x*=2;
			if (x>=1)
			{
				ret[j]='1';
				x--;
			}
			else
				ret[j]='0';
		}
	}
	return ret;
}

double todec(char *bin)
{
	double out = 0;
	double neg = 0;
	size_t i =0;
	if (bin[i]=='2')
	{
		neg = 1;
		i++;
	}
	while(bin[i] && bin[i]!=',')
		i++;
	
	if (bin[i])
	{
		size_t coma = i-1;
		int cpt = 0;
		for(;coma>0;coma--,cpt++)
		{
			if(bin[coma]=='1')
				out+= pow(2,cpt);
		}
		if(bin[coma]=='1')
			out+=pow(2,cpt);

		coma = i+1;
		cpt = -1;
		for(;bin[coma];coma++,cpt--)
		{
			if(bin[coma]=='1')
				out+=pow(2,cpt);
		}
	}
	else
	{
		i--;
		size_t cpt =0;
		for(;i>0;i--,cpt++)
    {
      if(bin[i]=='1')
        out+= pow(2,cpt);
    }
		if(bin[i]=='1')
      out+=pow(2,cpt);
	}
	if (neg==1)
		out*=-1;
	return out;

}

void Mat2File(char *path, double **mat, size_t lines, size_t cols)
{
	FILE *file;
	file = fopen(path, "w+");
	fprintf(file, "%s %s\n",tobin(lines),tobin(cols));
	for(size_t i=0; i<lines;i++)
	{
		for(size_t j=0;j<cols;j++)
			fprintf(file,"%s ",tobin(mat[i][j]));
		fputc('\n',file);
	}
	fclose(file);	
}

double **File2Mat(char *path)
{
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL)	
	{
		fclose(file);
		return NULL;
	}

	size_t lines, cols;
	char chain[255] = "";
	
	//lines
	fscanf(file,"%s",chain);
	lines = (size_t)todec(chain);

	//cols
	fscanf(file,"%s",chain);
	cols = (size_t)todec(chain);

	double **out = calloc(lines,sizeof(double*));
	for(size_t i =0; i<lines;i++)
	{
		out[i] = calloc(cols,sizeof(double));
		for(size_t j =0; j<cols;j++)
		{
			fscanf(file,"%s",chain);
			out[i][j] = (size_t)todec(chain);
		}
	}

	fclose(file);
	return out;
}



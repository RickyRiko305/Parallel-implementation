#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>

int main()
{   
	int n = pow(2,3);
//	int k = log2(n);

    int **a = (int**)malloc(sizeof(int*)*n);
    int **b = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++){
    	a[i] = (int*)malloc(sizeof(int)*n);
    	b[i] = (int*)malloc(sizeof(int)*n);
	}
	
	for(int i=0;i<n;i++)
	{
		#pragma omp parallel for
		for(int j=0;j<n;j++)
		{
			a[i][j] = i+2*j;
			b[i][j] = i+2*j; 
		}
	}

    //int temp;
	clock_t time_start,time_end;		// sequential algorithm
	time_start = clock();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)
		{
			int temp = b[i][j];
			b[i][j] = b[j][i];
			b[j][i] = temp;
		}
	}
	time_end = clock();
	double time_sequential = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
	for(int i=0;i<n;i++)
	{
		
		for(int j=0;j<n;j++)
		{
			printf("%d ",a[i][j]);
			//b[i][j] = i+j; 
		}
		printf("\n");
	}
	printf("\nTime taken by sequential algorithm is %f\n",time_sequential);

	


	time_start = clock();
	#pragma omp parallel for		// parallel algorithm
	for(int i=0;i<n;i++)
	{
		#pragma omp parallel for
		for(int j=i+1;j<n;j++)
		{
			int temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}
	time_end = clock();
	double time_parallel = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
	for(int i=0;i<n;i++)
	{
		
		for(int j=0;j<n;j++)
		{
			printf("%d ",b[i][j]);
			//b[i][j] = i+j; 
		}
		printf("\n");
	}
	printf("\nTime taken by parallel algorithm is %f\n",time_parallel);

	printf("\n--->SPEED UP = %f",time_sequential/time_parallel);
	return 0;
}

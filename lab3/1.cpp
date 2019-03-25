#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>

int main(){
	clock_t t0,t1;
	long int n = pow(2,15);
	long int *a = (long int*) malloc (sizeof(long int)*n);
	long int **b = (long int**) malloc (sizeof(long int*)*n);
	for(long int i=0; i<n; i++){
		b[i] = (long int*) malloc (sizeof(int)*n); 
	}
	long int *c = (long int*) malloc(sizeof(long int)*n);
	
	for(long int i=0;i<n; i++){
		a[i] = 1;
	}
	for(long int i=0; i<n; i++){
		for(long int j=0; j<n; j++){
			b[i][j] = 1;
		}
	}
		
	///for sequence start
	t0 = clock();
	long int sum=0;
	for(long int i=0; i<n; i++){
		for(long int j=0; j<n; j++){
			sum += (b[i][j] * a[j]);
		}
		c[i] = sum;
		sum=0;
	}
	t1 = clock();
	printf("sequence time taken:%f\n",(double)(t1-t0)/CLOCKS_PER_SEC);
//	for(int i=0; i<10; i++){
//		printf("%d\n",c[i]);
//	}
	///sequence end
	
	//parallel
	t0 = clock();
	long int *temp = (long int*) malloc(sizeof(long int)*n);
	long int *d = (long int*) malloc(sizeof(long int)*n);
	for(long int i=0; i<n ;i++){
		#pragma omp parallel for
		for(long int j=0; j<n; j++){
			temp[j] = a[j]*b[i][j];
		}
		for(long int j=0; j<15; j++){
			#pragma omp parallel for
			for(long int k=0 ;k<n/pow(2,j); k++){
				//temp[k] = (b[i][2*k] * temp[2*k]) + (b[i][2*k+1] * temp[2*k+1]); 
				temp[k] = temp[2*k] + temp[2*k+1]; 
			}
		}
		d[i] = temp[0];
	}
	t1 = clock();
	printf("parallel time taken:%f\n",(double)(t1-t0)/CLOCKS_PER_SEC);
//	for(long int i=0; i<10; i++){
//		printf("%d\n",d[i]);
//	}
	//parallel
	
	
	
	return 0;
}


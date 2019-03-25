#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>
using namespace std;

int main(){ 
  clock_t time_start,time_end;
 int n = pow(2,14);
    int *a = new(nothrow) int[n];
    int *b = new(nothrow) int[n];
    int *next = new(nothrow) int[n];
    int *temp = new(nothrow) int[n];
    
    for(int i=0; i<n; i++){
    	a[i] = rand();
    	b[i] = 1;    	
	}
	
	//sequence
    time_start = clock();
    int min=pow(10,9);
    for(int i=0; i<n; i++){
    	if(min>a[i]){
    		min = a[i];
		}
	}
	time_end = clock();
	cout<<"min "<<min<<endl;
	double time_sequential = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
    printf("\nTime taken by sequence algorithm is %f\n",time_sequential);
	
	//parallel
	time_start = clock();
	//#pragma omp parallel
	for(int i=1; i<=log(n)/log(2); i++){
		#pragma omp parallel
		for(int j=0; j<n/pow(2,i); j++){

            int x;
            x = n/pow(2,i);
            if(a[j] > a[j+x]){
            	a[j] = a[j+x];
			}
			
		}
	}
	
	time_end = clock();
	cout<<"min "<<a[0]<<endl;
    
    time_sequential = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
    printf("\nTime taken by parallel algorithm is %f\n",time_sequential);
    
    
    

 return 0;
}

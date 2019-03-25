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
    	a[i]= i+1;	
    	b[i]=1;
    	next[i] = i+1;
	}
	next[n-1] = -1;
    
    time_start = clock();
    #pragma omp parallel for
    for(int i=0; i<n; i++){
    	if((a[i]%2==0) ){
    		b[i] = 0;
		}
		else if((a[i]%5==0)){
			b[i] = 0;
		}
	}
	

    while(next[0]!=-1){
    	#pragma omp parallel 
    	for(int i=0; i<n; i++){
    		if(next[i]!=-1){
    			temp[next[i]] = b[i] + b[next[i]];
    			next[i] = next[next[i]];
			}
		}
		
		#pragma omp parallel
		for(int i=1; i<n; i++){
			b[i] = temp[i];
			
		}

	}
	
	int t ;
	t = b[n-1];
	int *mainval = new(nothrow) int[t];

	if( b[0]!=0 ){
		mainval[b[0]-1] = a[0];
		
	
	}
	
	#pragma omp parallel
	for(int i=1; i<n;i++){
		if((b[i] != b[i-1])){
			mainval[b[i]-1] = a[i];
		}
	}
	time_end = clock();
	double time_sequential = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
    printf("\nTime taken by parallel algorithm is %f\n",time_sequential);

	
	
	//sequence  ***********************************
	int	size=0;
	int *new_a = new(nothrow) int[n];
	time_start=clock();
	for(int i=0;i<n;i++)
	{
		if(a[i]%2!=0 && a[i]%5!=0 )
		{
			new_a[size++]=a[i];		
		}
	}
	time_end=clock();
	
	printf("\nTime taken by sequence algorithm is %f\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);
    
    
	
	return 0;
}

#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>
using namespace std;

int main(){ 
    clock_t time_start,time_end;  
    int n = pow(2,14);
    //int *a = new(nothrow) int[n];
    int *b = new(nothrow) int[n];
    int *next = new(nothrow) int[n];
    int *temp = new(nothrow) int[n];
    
    char charac[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                     'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 's', 'r', 't',
                     'u', 'v', 'w', 'x', 'y', 'z'};
    char allchar[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                     'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 's', 'r', 't',
                     'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G',
                     'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'S', 'R', 'T',
                     'U', 'V', 'W', 'X', 'Y', 'Z'};                 
             
	char *a = (char*)malloc(sizeof(char)*n);   
    for(int i=0; i<n; i++){
    	int p;
    	p = rand()%52;
    	a[i]= allchar[p];	
    	b[i]=1;
    	next[i] = i+1;
	}
	next[n-1] = -1;
    //cout<<a[1]<<endl;
    ///parallel*******************************************************************
    time_start = clock();
    #pragma omp parallel for
    for(int i=0; i<n; i++){
    	#pragma omp parallel for
    	for(int j=0; j<26; j++){
    		if((a[i] == charac[j]) ){
    			b[i] = 0;//'\0';
			}		
		}
    	
	}
	

	cout<<"\n";
	
    //cout<<a[1];
    //temp[0] = 
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

	int t ;
	t = b[n-1];
	
	char *mainval = (char*)malloc(sizeof(char)*t);

	if( b[0]!=0 ){
		mainval[b[0]-1] = a[0];
	}
	
	#pragma omp parallel
	for(int i=1; i<n;i++){
		if( (b[i] != b[i-1])){
			mainval[b[i]-1] = a[i];
		}
	}
	time_end = clock();
	double time_sequential = (double)(time_end-time_start)/(CLOCKS_PER_SEC);
    printf("\nTime taken by parallel algorithm is %f\n",time_sequential);

	cout<<"\n";

	
	//sequence*********************************************************************
	int size=0;
	char *new_a = (char*)malloc(sizeof(char)*n);
	time_start=clock();
	for(int i=0;i<n;i++)
	{
		if(a[i]>='A' && a[i]<='Z')
		{
			new_a[size++]=a[i];
		}
	}
	time_end=clock();
	
	printf("\nTime taken by sequence algorithm  %f\n",(double)(time_end-time_start)/CLOCKS_PER_SEC);
    
    
	
	return 0;
}

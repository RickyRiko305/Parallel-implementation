#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>
using namespace std;
int main(){
	clock_t t0,t1;
	long int n = pow(2,15);
	FILE  *file;
	file = fopen("text.txt","w");
//	if(file==null){
//		printf("the file does not exist\n");
//		exit -1;
//	}	
	
	char charac[38] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                     'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 's', 'r', 't',
                     'u', 'v', 'w', 'x', 'y', 'z','1', '2', '3', '4', '5', '6', '7',
                     '8', '9', '0',' ','\n'};
	
	for(int i=0; i<n; i++){
		fprintf(file, "%c", charac[rand()%38]); //alphabet[rand() % MAX];
	}
	fclose(file);
	
	file = fopen("text.txt","r");
	
	char ch;
	int v=0,con=0,digit=0;
	int v1=0,con1=0,digit1=0;
	t0 = clock();
	while (1) {
        ch = fgetc(file);
        if (ch == EOF)
            break;
        else if(ch =='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') v++;
        else if(ch >'a' && ch<='z')con++;
        else if(ch >='0' && ch<='9') digit++;
    }
    t1 = clock();
    cout<<"number of vowel = "<<v<<endl;
	cout<<"number of consonant = "<<con<<endl;
    cout<<"number of digit = "<<digit<<endl;
		
    printf("sequence time taken:%f\n",(double)(t1-t0)/CLOCKS_PER_SEC);    
    
    fclose(file);
    
    con=0,digit=0,v=0;
    t0 = clock();
    #pragma omp parallel
    {
    	file = fopen("text.txt","r");
    	int nthread,tid;
    	tid = omp_get_thread_num();
    	nthread = omp_get_num_threads();
    //	fseek(file,nthread,SEEK_CUR);
    	for(int i=tid;i<n; i+=nthread){
    		#pragma omp critical
    		{
    			ch = fgetc(file);
    			fseek(file,nthread-1,SEEK_CUR);
			}
    		
    	
        	if (ch == EOF)
         	   break;
       	    else if(ch =='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') v++;
      	    else if(ch >'a' && ch<='z')con++;
            else if(ch >='0' && ch<='9') digit++;
            //else if(ch== '\n') newline++,s++;
            //else if(isspace(ch)) s++;
		}
		#pragma omp critical
		{
			v1+=v;
			con1+=con;
			digit1+=digit;
		}
	}
    
    t1 = clock();
    cout<<"number of vowel = "<<v1<<endl;
	cout<<"number of consonant = "<<con1<<endl;
    cout<<"number of digit = "<<digit1<<endl;
    printf("parallel time taken:%f\n",(double)(t1-t0)/CLOCKS_PER_SEC);
    fclose(file);
    
	return 0;
}


#include<stdio.h>
/*Czteropuktowy atraktor dla r=3.48*/
void Logistics(int T,double r,double Log[]){
    int i;
    Log[0]=0.5;
    for(i=1;i<T;i++){
        Log[i]=r*Log[i-1]*(1-Log[i-1]);
    }
}

void Write(int T,double Log[]){
    int i;
    for(i=0;i<T;i++){
        printf("%d %f\n",i,Log[i]);
    }
}
        

int main(int argc,char *argv[]){
    /*Parametr value*/
    double r=atof(argv[1])/(double)(100);
    printf("%f %c\n",r,argv[1]);
    
    /*Number of iteration*/
    int T=atoi(argv[2]);
    
    /*Table of function values*/
    double Log[T];
    
    Logistics(T,r,Log);
        
    Write(T,Log);
        
    return 0;
}

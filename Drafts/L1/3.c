#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define p 1

int i,T[n],N[n],W[p];

int Deck(){
    int j,c=0,k,l;
    for(j=0;j<n;j++) N[j]=0;
    gsl_rng_env_setup();
    gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
    for(j=0;j<n;j++){
        l=0;
        do{k=((int)gsl_rng_uniform(r)*100);
            if(k!=0 && N[k-1]==0){
                T[j]=k;
                N[k-1]=1;
                l=1;
            }
        }while(l==0);
    }
    for(j=0;j<n;j++) if(T[j]==j+1) c++;
    return c;
}
        
float Avg(){
    int j;
    float A=0;
    for(j=0;j<p;j++) A+=W[j];
    A=A/((float)p);
    return A;
}
int main(){
    for(i=0;i<p;i++) W[i]=Deck();
    printf("Average outcome is: %.5f\n",Avg());
    system("pause");
    return 0;
}

#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define t 1

int T[2*n+1];

void RW(){
    int j,l,x=0;
    float p;
    gsl_rng_env_setup();
    gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
    for(j=1;j<=n;j++){
        p=gsl_rng_uniform(r);
        if(p>0.5) x++;
        else x--;
    }
    T[x+100]++;
}
        

int main(void){
    int i;
    for(i=0;i<2*n+1;i++) T[i]=0;
    for(i=0;i<t;i=i++) RW();
    for(i=0;i<2*n+1;i++) printf("%d %d\n",i-100,T[i]); 
    system("pause"); 
    return 0;
}

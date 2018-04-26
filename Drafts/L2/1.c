#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100

void RW(int k){
    int j,l,x=0;
    float p;
    gsl_rng_env_setup();
    gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
    for(j=1;j<=k;j++){
        printf("%d %d\n",x,j);
        p=gsl_rng_uniform(r);
        if(p>0.5) x++;
        else x--;
    }
    printf("\n");
}
        

int main(void){
    int i;
    for(i=10;i<=n;i=i+10) RW(i);   
    system("pause"); 
    return 0;
}

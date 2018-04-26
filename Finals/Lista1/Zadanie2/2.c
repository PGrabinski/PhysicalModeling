#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 10000000
#define w 0.3989422804

int i;
double C[2],S;

int MC(){
    gsl_rng_env_setup();
    gsl_rng *r= gsl_rng_alloc(gsl_rng_mt19937);
    int c=0;
    for (i=0;i<n;i++){
        C[0]=gsl_rng_uniform(r);
        C[1]=gsl_rng_uniform(r);
        if(exp((-0.5)*C[1]*C[1])>=C[0]) c++;
    }
    return c;
}

int main(void){
    S=w*2*MC()/((float) n);
    printf("After integration: %.5f \nIntegration by Wolfram: 0.682689\n",S);
    system("pause");
    return 0;
}

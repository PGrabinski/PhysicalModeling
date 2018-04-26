#include <stdio.h>
#include <gsl/gsl_rng.h>


/*Setting the Lattice*/
void Set(gsl_rng *q,int L,double p, int Lattice[][L]){
    int i,j;
    double r;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            r=gsl_rng_uniform(q);
            if(r<p) Forest[i][j]=1;
            else Lattice[i][j]=-1;
        }
    }
}

/*Maxiumum function*/
int Max(int a, int b){
    if(a>b) return a;
    else return b;
}

/*Energy change*/
int EnergyChange(int L, int Lattice[][L]){
    int To

int main(int argc,char *argv[]){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    const int T=10000;
    int i;
    int L=atoi(argv[1]);
    double p=0.5;
    int Lattice[L][L];
    
    return 0;
}

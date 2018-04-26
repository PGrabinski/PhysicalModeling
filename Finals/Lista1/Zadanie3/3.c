#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define p 1000000

int T[n],k,N[n],W[p];

void Rewrite(int z){
        int i,y=0,l;
        for(i=0;i<k;i++){
        if(i!=z-1){
            T[i]=T[y];
        }
        else{
            y++;
        }
        y++;
    }
    /*for(l=0;l<k-1;l++) printf("%d ",T[l]);
    printf("\n%d\n",z);*/
    k--;
}

int Count(){
    int i,l=0;
    for(i=0;i<n;i++){
        if(N[i]==i+1) l++;
    }
    return l;
}

int Deck(gsl_rng *r){
    int i,j,c=0,q;
    k=n;
    for(j=0;j<n;j++) N[j]=0;
    for(j=0;j<n;j++) T[j]=j+1;
        for(i=0;i<n;i++){
                q=((int) (gsl_rng_uniform(r)*(k-1)+1));
                N[i]=T[q];
                Rewrite(q);
    }
    c=Count();
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
    int w;
    k=n;
    gsl_rng_env_setup();
    gsl_rng *g=gsl_rng_alloc(gsl_rng_mt19937);
        for(w=0;w<p;w++) W[w]=Deck(g);
    printf("Average outcome is: %.5f\n",Avg());
    system("pause");
    return 0;
}

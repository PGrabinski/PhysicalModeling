#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define p1 0.2
#define p2 0.8
#define t 100

int T[201];



void RW(gsl_rng *r,float k){
    int j,x=0,d=1;
    float p;
    for(j=1;j<=n;j++){
        p=gsl_rng_uniform(r);
        if(d==1){
            if(p<=k){
                d=1;
                x++; 
            }   
            else{
                x--;
                d=-1;
            }
        }
        else{
            if(p>k){
                x++;
                d=1; 
            }  
            else{
                d=-1;
                x--; 
            }
            
        }
    }
        T[x+100]++;
}

void MK(float k){
    int i;
    for(i=0;i<2*n+1;i++) T[i]=0;
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_default);
    for(i=0;i<t;i++) RW(q,k);
}

int main(void){
    int i;
    MK(p1);
    for(i=0;i<2*n+1;i++) printf("%d %d\n",i-100,T[i]);
    printf("\n");
    MK(p2);
    for(i=0;i<2*n+1;i++) printf("%d %d\n",i-100,T[i]);
    system("pause"); 
    return 0;
}
    

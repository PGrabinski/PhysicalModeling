#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define p1 0.2
#define p2 0.8
#define p3 0.5
#define P 5

int T[5];

void RW(float k,int o){
    int j,x=0,d=1,s=0;
    float p;
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_default);
    for(j=1;j<=(o+1)*P;j++){
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
        s+=x;
    }
        s=s*s;
        T[o]=s;
}


int main(void){
    int i;
    for(i=0;i<P;i++) RW(p1,i);
    for(i=0;i<2*n+1;i++) printf("%d %d\n",i-100,T[i]);
    printf("\n");
    MK(p2);
    for(i=0;i<2*n+1;i++) printf("%d %d\n",i-100,T[i]);
    system("pause"); 
    return 0;
}
    

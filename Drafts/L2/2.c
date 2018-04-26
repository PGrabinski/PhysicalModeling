#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define p1 0.2
#define p2 0.8


void RW(float k){
    int j,l,x=0,d=1;
    float p;
    gsl_rng_env_setup();
    gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
    for(j=1;j<=n;j++){
        p=gsl_rng_uniform(r);
        if(d==1){
            if(p<=k){
                d=1;
                x++;
                printf("%d %d\n",j,x);
            }   
            else{
                x--;
                d=-1;
                printf("%d %d\n",j,x);
            }
        }
        else{
            if(p>k){
                d=1;
                x++; 
                printf("%d %d\n",j,x); 
            }  
            else{
                x--;
                d=-1;
                printf("%d %d\n",j,x);
            }
            
        }
    }
    
    printf("\n");
}
        

int main(void){
    int i;
    RW(p1);
    RW(p2);
    system("pause"); 
    return 0;
}
    

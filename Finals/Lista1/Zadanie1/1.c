#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <math.h>
#define n 10000000
#define W 20

int i,j,k,l,d=0;
float Wek[W],P;

int MC(int q){
	int c=0;
	float sum=0;
	
    gsl_rng_env_setup();
	gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
	
	for(j=0;j<q;j++){
                     for (i=0;i<d;i++){
    			Wek[i]=gsl_rng_uniform (r);
            }
		for(i=0;i<d;i++){
			sum+=Wek[i]*Wek[i];
		}
		if(sum<=1) c++;
		sum=0;
	}
	gsl_rng_free (r);
	return c;
}

int main (void){
    for(l=1000;l<=n;l=l*10){
        printf("Number of samples: %d\n", l);
        for(k=1;k<=W;k++){
            d=k;
	       P=pow(2,d)*MC(l)/((float) l);
            printf("The volume for d=%d is: %.5f\n", d,P);
        }
    }
    system("pause");
    return 0;
}

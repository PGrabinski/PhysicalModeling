#include<iostream>
#include<gsl/gsl_rng.h>
int main()
{unsigned long int zarodek;
gsl_rng *r= gsl_rng_alloc(gsl_rng_mt19937);
cout<<"seed >0 = "; cin>>zarodek;
gsl_rng_set(r, zarodek);
for(int n=1;n<=20;n++)
{double u=gsl_rng_uniform(r);
cout<<n<<" "<<u<<endl; }
return 0;
}

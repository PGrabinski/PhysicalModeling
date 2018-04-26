#include<stdio.h>
#include<math.h>
#include<gsl/gsl_rng.h>

    double d_Mag=0;
    double d_E=0;
    double d_Magt=0;
    double d_Et=0;
    double d_E2=0;
    double d_Mag2=0;
    double d_MAG=0;
        
/*Setting the Lattice*/
void Set(int n_L, int n_Lattice[][n_L],gsl_rng *q){
    int i,j;
    for(i=0;i<n_L;i++){
        for(j=0;j<n_L;j++){
            if(gsl_rng_uniform(q)<0.5) n_Lattice[i][j]=1;
            else n_Lattice[i][j]=-1;
        }
    }
}

/*Energy change*/
double d_EnergyDif(int n_L,int n_Lattice[][n_L],int x, int y){
    int i,j;
    int n_Spin=0;
    double d_J=1;
    for(i=x-1;i<x+1;i++){
        for(j=y-1;j<y+1;j++){
            if(i!=j)
                n_Spin+=n_Lattice[(i+n_L)%n_L][(j+n_L)%n_L];
        }
    }
    return 2*n_Lattice[x][y]*n_Spin*d_J;
}

void d_Begin(int n_L,int n_Lattice[][n_L]){
    int i,j;
    int n_TotSpin=0;
    double d_Energy=0;
    for(i=0;i<n_L;i++){
        for(j=0;j<n_L;j++){
            n_TotSpin+=n_Lattice[i][j];
            d_Energy+=d_EnergyDif(n_L,n_Lattice,i,j)/4.0;
        }
    }
    d_Mag=n_TotSpin;
    d_E=d_Energy;
}

void MChain(int n_L,int n_Lattice[][n_L],gsl_rng *q,double d_rT){
    int x=(int)(gsl_rng_uniform(q)*(n_L));
    int y=(int)(gsl_rng_uniform(q)*(n_L));
    double d_edif=d_EnergyDif(n_L,n_Lattice,x,y);
    double p;
    if(d_edif>0)
        p=exp(-d_rT*d_edif);
    else
        p=1;
    if(gsl_rng_uniform(q)<=p){
        n_Lattice[x][y]=-n_Lattice[x][y];
        d_Mag+=-2*n_Lattice[x][y];
        d_Magt+=d_Mag;
        d_E+=d_edif;
        d_Et+=d_E;
        d_Mag2+=d_Mag*d_Mag;
        d_MAG+=abs(d_Mag);
    }
    
}

int main(int argc,char *argv[]){
    int n_L=atoi(argv[1]);
    int n_Lattice[n_L][n_L];
    int n_N=n_L*n_L;
    const int n_T=1000;
    
    gsl_rng_env_setup();
    gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
    
    double T;
    for(T=0.5;T<=4.0;T+=0.1){
        double d_rT=1.0/T;
        
        Set(n_L,n_Lattice,r);
        d_Begin(n_L,n_Lattice);
        
        int i;
        for(i=0;i<n_T;i++){
            int j;
            for(j=0;j<n_N;j++)
                MChain(n_L,n_Lattice,r,d_rT);
        }
        
        for(i=0;i<n_T;i++){
            int j;
            for(j=0;j<n_N;j++)
                MChain(n_L,n_Lattice,r,d_rT);                
        }
            printf("%.1f %f %f %f\n",T,(d_Mag/(double)(n_T)),((d_E2-d_Et*d_Et)/(double)(T*T*n_N*n_T)),(double)((d_Mag2-d_Magt*d_Magt)/(double)(T*n_N*n_T)));
    }
    return 0;
}

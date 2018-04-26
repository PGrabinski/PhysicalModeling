#include <stdio.h>
#include <gsl/gsl_rng.h>

/*Setting the Lattice*/
void Set(gsl_rng *q,int L,double p, int Forest[][L]){
    int i,j;
    double r;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            r=gsl_rng_uniform(q);
            if(r<p) Forest[i][j]=1;
            else Forest[i][j]=0;
            /*printf("%d",Forest[i][j]);*/
        }
        /*printf("\n");*/
    }
}

/*Maxiumum function*/
int Max(int a, int b){
    if(a>b) return a;
    else return b;
}

/*Measuring the time of firewalk*/
int Time(int L,int Forest[][L]){
    int i,j,t=2;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            t=Max(Forest[i][j],t);
        }
    }
    return t-2;
}

/*Performing the firewalk*/    
void Percolation(int L,int Forest[][L]){
    int i,j,t,b=0;
    for(i=0;i<L;i++){
        if(Forest[i][0]==1) Forest[i][0]=2;
    }
    for(t=2;;t++){
        b=0;
        for(i=0;i<L;i++){
            for(j=0;j<L;j++){
                if(Forest[i][j]==t){
                    if(i-1>=0)
                        if(Forest[i-1][j]==1){
                            Forest[i-1][j]=t+1;
                            b=1;
                        }
                    if(i-1>=0 && j-1>=0)
                        if(Forest[i-1][j-1]==1){
                            Forest[i-1][j-1]=t+1;
                            b=1;
                        }
                    if(j-1>=0)
                        if(Forest[i][j-1]==1){
                            Forest[i][j-1]=t+1;
                            b=1;
                        }
                    if(i+1<L)
                        if(Forest[i+1][j]==1){
                            Forest[i+1][j]=t+1;
                            b=1;
                        }
                    if(j+1<L)
                        if(Forest[i][j+1]==1){
                            Forest[i][j+1]=t+1;
                            b=1;
                        }
                    if(i+1<L && j+1<L)
                        if(Forest[i+1][j+1]==1){
                            Forest[i+1][j+1]=t+1;
                            b=1;
                        }
                    if(i-1<=0 && j+1<L)
                        if(Forest[i-1][j+1]==1){
                            Forest[i-1][j+1]=t+1;
                            b=1;
                        }
                    if(i+1<L && j-1>=0)
                        if(Forest[i+1][j-1]==1){
                            Forest[i+1][j-1]=t+1;
                            b=1;
                        }
                }
            }
        }
        if(b!=1) break;
    }
}

int main(int argc,char *argv[]){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    const int T=1000000;
    int i;
    double time=0;
    int L=atoi(argv[1]);
    double p=atof(argv[2]);
    /*int L=20;
    double p=0.6;*/
    for(i=0;i<T;i++){
    int Forest[L][L];
    Set(q,L,p,Forest);
    Percolation(L,Forest);
    time+=Time(L,Forest);
    }
    time=time/(double)(T);
    printf("%.2f %f\n",p,time);
    system("pause");  
    return 0;
}

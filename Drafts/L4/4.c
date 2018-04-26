#include <stdio.h>
#include <gsl/gsl_rng.h>

/*pixel*/
typedef struct{
  int R;
  int G;
  int B;
}RGB;

/*Setting the Lattice*/
void Set(gsl_rng *q,int L,double p, int Forest[][L]){
    int i,j;
    double r;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            r=gsl_rng_uniform(q);
            if(r<p) Forest[i][j]=1;
            else Forest[i][j]=0;
            //printf("%d",Forest[i][j]);
        }
        //printf("\n");
    }
}

/*Maxiumum function*/
int Max(int a, int b){
    if(a>b) return a;
    else return b;
}

/*Fire spreading*/
int FireSpread(int L,int x, int y,int t,int Forest[][L]){
    if(Forest[x][y]==1){
        Forest[x][y]=t;
        if(x-1>=0 && y-1>=0){
            FireSpread(L,x-1,y-1,t,Forest);
        }
        if(x-1>=0 && y+1<L){
            FireSpread(L,x-1,y+1,t,Forest);
        }
        if(x-1>=0){
            FireSpread(L,x-1,y,t,Forest);
        }
        if(x+1<L && y-1>=0){
            FireSpread(L,x+1,y-1,t,Forest);
        }
        if(x+1<L && y+1<L){
            FireSpread(L,x+1,y+1,t,Forest);
        }
        if(x+1<L){
            FireSpread(L,x+1,y,t,Forest);
        }
        if(y-1>=0){
            FireSpread(L,x,y-1,t,Forest);
        }
        if(y+1<L){
            FireSpread(L,x,y+1,t,Forest);
        }
       return 1;
    }
    else return 0;
}

int Check(int L,int Forest[][L]){
    int i,j,t=2;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            t=Max(Forest[i][j],t);
        }
    }
    return t;
}

/*Cluster searching*/
void ClusterSearch(int L,int Forest[][L]){
    int i,j,k=2;
        for(i=0;i<L;i++){
            for(j=0;j<L;j++){
                if(FireSpread(L,i,j,k,Forest)==1){
                    k++;
                    //printf("mam!\n");
                }
            }
        }
}
double CountMass(int L, double p, int f){
    return (double)(p*L*L/(double)f);
}

void Mass(int L, int N, int Forest[][L],int ClusterMasses[]){
        int i,j,k;
            for(j=0;j<L;j++){
                for(k=0;k<L;k++){
                        if(Forest[j][k]!=0)ClusterMasses[Forest[j][k]-2]++;
                }
            }
}

int MassCheck(int f,int N,double p, int ClusterMasses[],int L,int Forest[][L]){
    double MinMass=L*L*p/(double)(f);
    int i;
    int GoodClust=0;
    for(i=0;i<N;i++){
        if(ClusterMasses[i]>=MinMass) GoodClust++;
    }
    return GoodClust;
}

int main(int argc,char *argv[]){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    const int T=10000;
    int i;
    double TotClust=0,Clust3=0,Clust2=0;
    int L=atoi(argv[1]);
    double p=atof(argv[2])/(double)(100);
    RGB o[L][L];
    int Forest[L][L];
    for(i=0;i<T;i++){
        Set(q,L,p,Forest);
        ClusterSearch(L,Forest);
        int N=Check(L,Forest);
        int ClusterMasses[N];
        Mass(L,N,Forest,ClusterMasses);
        TotClust+=N;
        Clust3+=MassCheck(3,N,p,ClusterMasses,L,Forest);
        Clust2+=MassCheck(2,N,p,ClusterMasses,L,Forest);
    }
    TotClust=TotClust/(double)(T);
    Clust2=Clust2/(double)(T);
    Clust3=Clust3/(double)(T);
    printf("%.2f %f %.2f %f %.2f %f\n",p,TotClust,p,Clust3,p,Clust2);
    return 0;
}

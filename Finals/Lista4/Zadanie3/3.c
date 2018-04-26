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

//zbedne
/*Maxiumum function*/
int Max(int a, int b){
    if(a>b) return a;
    else return b;
}

/*Copping to file*/
void Write(FILE *w,int L,RGB o[][L]){
    int i,j;
    fprintf(w,"P3\n#DLA\n%d %d\n255\n",L,L);
    for(j=0;j<L;j++){
       for(i=0;i<L;i++){
           fprintf(w,"%d %d %d ",o[j][i].R,o[j][i].G,o[j][i].B);
       }
    }
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

void Paint(int L,int N,int Forest[][L],RGB o[][L]){
    int i,j;
    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            if(Forest[i][j]==0){
                o[i][j].R=0;
                o[i][j].G=0;
                o[i][j].B=0;
            }
            else{
                if(Forest[i][j]/(double)(N)<=0.33){
                    o[i][j].R=(int)(Forest[i][j]/(double)(N)*255);
                    o[i][j].G=0;
                    o[i][j].B=0;
                }
                if(Forest[i][j]/(double)(N)>0.33 && Forest[i][j]/(double)(N)<=0.67){
                    o[i][j].R=(int)(Forest[i][j]/(double)(N)*255);
                    o[i][j].G=(int)(Forest[i][j]/(double)(N)*255);
                    o[i][j].B=0;
                }
                if(Forest[i][j]/(double)(N)>0.67){
                    o[i][j].R=(int)(Forest[i][j]/(double)(N)*255);
                    o[i][j].G=(int)(Forest[i][j]/(double)(N)*255);
                    o[i][j].B=(int)(Forest[i][j]/(double)(N)*255);
                }
            }
        }
    }
}


void Mass(int L, int N,int Forest[][L]){
        int i,j,k,Mass;
        for(i=0;i<N;i++){
            Mass=0;
            for(j=0;j<L;j++){
                for(k=0;k<L;k++){
                        if(Forest[j][k]==i+2) Mass++;
                }
            }
            printf("Masa %d klastra wynosi: %d\n",i+1,Mass);
        }

}

int main(int argc,char *argv[]){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    int i;
    int L=atoi(argv[1]);
    double p=atof(argv[2]);
    //int L=100;
    //double p=0.6;
    printf("%f\n",p);
    RGB o[L][L];
    int Forest[L][L];
    Set(q,L,p,Forest);
    ClusterSearch(L,Forest);
    int N=Check(L,Forest);
    Paint(L,N,Forest,o);
    FILE *a=fopen("klaster08.ppm", "w");
    Write(a,L,o);
    fclose(a);
    Mass(L,N,Forest);
    //system("pause");
    return 0;
}

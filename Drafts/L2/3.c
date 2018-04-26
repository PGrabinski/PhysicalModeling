#include <stdio.h>
#include <gsl/gsl_rng.h>
#define n 100
#define H 1000
#define W 1000

int Board[H][W];

void Clean(){
    int i,j;
    for(i=0;i<H;i++) for(j=0;j<W;j++) Board[i][j]=0;
}

void RW(gsl_rng *r){
    int i,j,k,x=500,y=500,o=0;
    float p;
    Board[x][y]=1;
    for(k=0;k<t;k++){
        if(Board[x-1][y]==0)o++;
        if(Board[x+1][y]==0)o++;
        if(Board[x][y-1]==0)o++;
        if(Board[x][y+1]==0)o++;
        switch(o){
            case 0:
                printf("Koniec\n");
                break;
            case 1:
                if(Board[x-1][y]==0){
                    Board[x-1][y]=1;
                    x--;
                }
                if(Board[x+1][y]==0){
                    Board[x+1][y]=1;
                    x++;
                }
                if(Board[x][y-1]==0){
                    Board[x][y-1]=1;
                    y--;
                }
                if(Board[x][y+1]==0){
                    Board[x][y+1]=1;
                    y++;
                }
                break;
            case 2:
                
        
        o=0;
    }
}
    
    

int main(void){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    Clean();
    RW(q);   
    return 0;
}

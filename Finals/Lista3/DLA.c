#include <stdio.h>
#include <gsl/gsl_rng.h>
#define W 200
#define H 200
#define n 1200

typedef struct{
  int R;
  int G;
  int B;
}RGB;

typedef struct{
    int x;
    int y;
}particle;

RGB o[H][W];

int Board[H][W];

/*Przygotowanie próbki*/
void Set(){
    int i,j;
    for(i=1;i<H;i++)
        for(j=1;j<W;j++)
            Board[i][j]=0;
    for(i=0;i<H;i++) Board[i][0]=1;
    for(i=0;i<H;i++) Board[i][W-1]=1;
    for(i=0;i<W;i++) Board[0][i]=1;
    for(i=0;i<W;i++) Board[H-1][i]=1;
}

/*B³¹dzenie losowe*/
particle RW(gsl_rng *q){
    particle u;
    u.x=H/2;
    u.y=W/2;
    float z;
    int t=1;
    do{
        if(Board[u.x-1][u.y]==0 && Board[u.x+1][u.y]==0 && Board[u.x][u.y-1]==0 && Board[u.x][u.y+1]==0){
            z=gsl_rng_uniform(q);
            if(z<1/((float) 4)) u.x++;
            if(z>=1/((float) 2) && z<3/((float) 4)) u.x--;
            if(z>=1/((float) 4) && z<1/((float) 2)) u.y++;
            if(z>=3/((float) 4) && z<=1) u.y--;
        }
        else{
            t=0;
            return u;
            break;
        }
    }while(t==1);
}
        
    

/*Inicjacja DLA i czas*/
void DLA(gsl_rng *q){
    int i,j;
    particle a;
    for(i=2;i<7;i++){
        for(j=0;j<n;j++){
            a=RW(q);
            Board[a.x][a.y]=i;
            
        }   
    }
}

/*kolorowanie*/
void Transform(){
    int i,j;
        for(i=0;i<H;i++){
	       for(j=0;j<W;j++){
                /*if(Board[i][j]==0){
                        o[i][j].G=255;
                        o[i][j].R=255;
                        o[i][j].B=255;
                }
                else{
                        o[i][j].B=157;
                        o[i][j].R=0;
                        o[i][j].G=113;
                }*/
                    
	           switch(Board[i][j]){
                    case 0:
                        o[i][j].G=0;
                        o[i][j].R=0;
                        o[i][j].B=0;
                        break;
                    
                    case 1:
                        o[i][j].G=100;
                        o[i][j].R=100;
                        o[i][j].B=100;
                        break;
                    case 2:
                        o[i][j].G=0;
                        o[i][j].R=255;
                        o[i][j].B=0;
                        break;
                    case 3:
                        o[i][j].G=0;
                        o[i][j].R=0;
                        o[i][j].B=255;
                        break;
                    case 4:
                        o[i][j].G=255;
                        o[i][j].R=0;
                        o[i][j].B=0;
                        break;
                    case 5:
                        o[i][j].G=255;
                        o[i][j].R=255;
                        o[i][j].B=0;
                        break;
                    case 6:
                        o[i][j].G=255;
                        o[i][j].R=255;
                        o[i][j].B=255;
                        break;
                }
                        

                        
	   }
    }
}
/*Zapis*/
void write(FILE *w){
    int i,j;
    fprintf(w,"P3\n#DLA\n%d %d\n255\n",W,H); 
    for(j=0;j<H;j++){
	   for(i=0;i<W;i++){
	       fprintf(w,"%d %d %d ",o[j][i].R,o[j][i].G,o[j][i].B);
	   }
    }
}

int main(void){
    gsl_rng_env_setup();
    gsl_rng *q=gsl_rng_alloc(gsl_rng_mt19937);
    Set();
    DLA(q);
    Transform();
    FILE *a=fopen("dla.ppm", "w");
    write(a);
    fclose(a);
    system("pause");  
    return 0;
}

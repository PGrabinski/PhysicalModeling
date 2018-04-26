#include <stdio.h>
#define W 1024  
#define H 760
#define T 40
#define Re 0
#define Im 0

/*pixel*/
typedef struct{
  int R;
  int G;
  int B;
}RGB;

/*complex number*/
typedef struct{
    double re;
    double im;
}complex;

RGB o[H][W];

/*Copping to file*/
void write(FILE *w){
    int i,j;
    fprintf(w,"P3\n#DLA\n%d %d\n255\n",W,H); 
    for(j=0;j<H;j++){
	   for(i=0;i<W;i++){
	       fprintf(w,"%d %d %d ",o[j][i].R,o[j][i].G,o[j][i].B);
	   }
    }
}

void Julia(){
    int i,j,k,t;
    complex u,v;
    for(i=0;i<H;i++){
        for(j=0;j<W;j++){
            u.re=(j/(double)W)*3-1.5;
            u.im=(i/(double)H)*2.5-1.25;
            /*printf("%f %f\n",u.re,u.im);*/
            for(k=0;k<T;k++){
                v.re=u.re;
                v.im=u.im;
                u.re=v.re*v.re-v.im*v.im+Re;
                u.im=2*v.re*v.im+Im;
                if(u.im*u.im+u.re*u.re>4){
                    /*printf("%f %f %d\n",u.re,u.im,t);*/
                    t=k;
                    break;
                }
            }
            /*printf("\n");*/
            o[i][j].R=(int)(t/(double)(T)*255);
            o[i][j].G=(int)(t/(double)(T)*255);
            o[i][j].B=(int)(t/(double)(T)*255);
        }
    }   
}

int main(){
    Julia();
    FILE *a=fopen("julia0.ppm", "w");
    write(a);
    fclose(a);
    return 0;
}

#include<stdio.h>
#define W 1024
#define H 768
#define T 300

/*pixel*/
typedef struct{
  int R;
  int G;
  int B;
}RGB;

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

void Mandelbrot(){
    int i,j,t;
    for(i=0;i<H;i++){
        for(j=0;j<W;j++){
            float x0=j/(float)(W)*3.5-2.5,y0=i/(float)(H)*2-1,x=0,y=0,xt=0;
            t=0;
        	while(x*x+y*y<4 && t<T){
                xt=x*x-y*y+x0;
            	y=2*x*y+y0;
            	x=xt;
                t++;
            }
            if(t/(float)(T)<1/(float)(3)){
                o[i][j].R=t/(float)(T)*3*255;
            }
            else{
                if(t/(float)(T)<2/(float)(3)){
                     o[i][j].R=255;
                     o[i][j].G=t/(float)(T)*3/2*255;
                }
                else{
                    o[i][j].R=255;
                    o[i][j].G=255;
                    o[i][j].B=t/(float)(T)*255;
                }
            }
        }
    }
}

int main(){
    Mandelbrot();
    FILE *a=fopen("mandelbrot.ppm", "w");
    write(a);
    fclose(a);
    return 0;
}

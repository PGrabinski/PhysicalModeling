#include<stdio.h>
#include<math.h>
#include<gsl/gsl_rng.h>
/*Particle*/
typedef struct{
    double x;
    double y;
    double Vx;
    double Vy;
}Particle;

/*Setting velocity*/
Particle v_SetV(Particle p_e,gsl_rng *rng_r){
    double d_tempvx,d_tempvy,d_l=gsl_rng_uniform(rng_r);
    p_e.Vx=gsl_rng_uniform(rng_r);
    p_e.Vy=sqrt(2-d_tempvx*d_tempvx);
    p_e.x=0;
    p_e.y=0;
    /*printf("Poczatek %f %f\n",p_e.Vx,p_e.Vy);*/
    return p_e;
}

/*Qucik power value*/
double d_QuickPower(double d_Base,int n_Power){
    if(n_Power==0)
        return 1;
    if(n_Power%2==1)
        return d_Base*d_QuickPower(d_Base,n_Power-1);
    else
        return d_QuickPower(d_Base,n_Power/2)*d_QuickPower(d_Base,n_Power/2);
}

/*Parameter w value*/
double d_GetW(double d_x,double d_y){
    return 639680*M_PI*d_QuickPower(cos(M_PI*d_x)*cos(M_PI*d_y),63);
}

/*X part of function f*/
double d_FunctionX(double d_x, double d_y,double d_w){
    if(d_x*d_x+d_y*d_y<=0.25)
        return d_w*sin(M_PI*d_x)*cos(M_PI*d_y);
    else
        return 0;
}

/*Y part of function f*/
double d_FunctionY(double d_x, double d_y, double d_w){
    if(d_x*d_x+d_y*d_y<=0.25)
        return d_w*cos(M_PI*d_x)*sin(M_PI*d_y);
    else
        return 0;
}

/*X part of Force*/
double d_ForceX(double d_x, double d_y, Particle p_e,double d_B, double d_w){
    return 2*sqrt(2)*d_B*p_e.Vy+d_FunctionX(d_x,d_y,d_w);
}

/*Y part of Force*/
double d_ForceY(double d_x, double d_y, Particle p_e,double d_B, double d_w){
    return -2*sqrt(2)*d_B*p_e.Vx+d_FunctionY(d_x,d_y,d_w);
}

/*Runge-Kutta Algorithm*/
void v_RKA(Particle p_e,double d_B,gsl_rng *rng_r,int n_N){
    int i;
    double d_w;
    double d_Vx,d_Vy;
    double d_h=0.0001;
    FILE *a=fopen("dane1.dat", "w");
    /*Wspolczynniki RK*/
    double d_a,d_b,d_c,d_d;
    for(i=0;i<n_N;i++){
        d_Vx=0;
        d_Vy=0;
        d_w=d_GetW(p_e.x,p_e.y);
        d_a=d_h*d_ForceX(p_e.x,p_e.y,p_e,d_B,d_w);
        d_b=d_h*d_ForceX(p_e.x+d_a*0.5,p_e.y+d_a*0.5,p_e,d_B,d_w);
        d_c=d_h*d_ForceX(p_e.x+0.5*d_b,p_e.y+0.5*d_b,p_e,d_B,d_w);
        d_d=d_h*d_ForceX(p_e.x+d_c,p_e.y+d_c,p_e,d_B,d_w);
        d_Vx=p_e.Vx+(d_a+2*d_b+2*d_c+d_d)/6.0;

        d_a=d_h*d_ForceY(p_e.x,p_e.y,p_e,d_B,d_w);
        d_b=d_h*d_ForceY(p_e.x+d_a*0.5,p_e.y+d_a*0.5,p_e,d_B,d_w);
        d_c=d_h*d_ForceY(p_e.x+0.5*d_b,p_e.y+0.5*d_b,p_e,d_B,d_w);
        d_d=d_h*d_ForceY(p_e.x+d_c,p_e.y+d_c,p_e,d_B,d_w);
        d_Vy=p_e.Vy+(d_a+2*d_b+2*d_c+d_d)/6.0;

        p_e.Vx=d_Vx;
        p_e.Vy=d_Vy;
        p_e.x+=p_e.Vx;
        p_e.y+=p_e.Vy;

        fprintf(a,"%.1f %.1f \n",p_e.x,p_e.y);
    }
}

int main(int argc, char *argv[]){
    double d_B=(double)(atoi(argv[1])/(double)(100.0));
    const int n_N=500000;

    gsl_rng_env_setup();
    gsl_rng *rng_r=gsl_rng_alloc(gsl_rng_mt19937);

    Particle p_e=v_SetV(p_e,rng_r);

    v_RKA(p_e,d_B,rng_r,n_N);
    system("PAUSE");
    return 0;
}

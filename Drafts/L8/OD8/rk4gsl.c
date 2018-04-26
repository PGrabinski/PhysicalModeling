#include<stdio.h>
#include<gsl/gsl_errno.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_odeiv2.h>
#include<math.h>

int func (double t, const double y[], double f[], void *params){
    double B=-10*2*sqrt(2);
    double w=639680*M_PI*pow(cos(M_PI*y[0])*cos(M_PI*y[1]),63);
    if(y[0]*y[0]+y[1]*y[1]<=0.25){
        f[0]=y[2];
        f[1]=y[3];
        f[2]=B*y[3]+w*sin(M_PI*y[0])*cos(M_PI*y[1]);
        f[3]=-B*y[2]+w*cos(M_PI*y[0])*sin(M_PI*y[1]);
    }
    else{
        f[0]=y[2];
        f[1]=y[3];
        f[2]=B*y[3];
        f[3]=-B*y[2];
    }
    return GSL_SUCCESS;
}

int main(){
    size_t dim=4;
    double eps_abs=1.e-6,eps_rel=0.;
    double stepsize=1e-6;
    double y[4]={0.6,0.01,-1.41,0.0};
    double t=0.0;
    double t1=100.0;
    int status;

    gsl_odeiv2_step    *s = gsl_odeiv2_step_alloc (gsl_odeiv2_step_rk4, dim);
    gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs, eps_rel);
    gsl_odeiv2_evolve  *e = gsl_odeiv2_evolve_alloc (dim);
    gsl_odeiv2_system sys = {func, NULL, dim, NULL};

    const int T=1000;
    int i;
    for(i=0;i<T;i++){
        status=gsl_odeiv2_evolve_apply(e,c,s,&sys,&t,t1,&stepsize,y);
        if(status!=GSL_SUCCESS){
            printf ("Troubles at %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1],y[2],y[3]);
            break;
        }
        printf ("%.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1],y[2],y[3]);
    }

    gsl_odeiv2_evolve_free (e);
    gsl_odeiv2_control_free (c);
    gsl_odeiv2_step_free (s);
    return 0;
}

#include "simulationrealization.h"

simulationRealization::simulationRealization(int gridSize):
    DIM(50), dt(0.4), visc(0.001),
    color_dir(0), vec_scale(1000), draw_smoke(0), draw_vecs(1),
    COLOR_BLACKWHITE(0), COLOR_RAINBOW(1), COLOR_BANDS(2),
    scalar_col(0), frozen(0)
{
    int i; size_t dim;

    dim     = gridSize * 2*(gridSize/2+1)*sizeof(fftw_real);        //Allocate data structures
    vx       = (fftw_real*) malloc(dim);
    vy       = (fftw_real*) malloc(dim);
    vx0      = (fftw_real*) malloc(dim);
    vy0      = (fftw_real*) malloc(dim);
    dim     = gridSize * gridSize * sizeof(fftw_real);
    fx      = (fftw_real*) malloc(dim);
    fy      = (fftw_real*) malloc(dim);
    rho     = (fftw_real*) malloc(dim);
    rho0    = (fftw_real*) malloc(dim);
    plan_rc = rfftw2d_create_plan(gridSize, gridSize, FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
    plan_cr = rfftw2d_create_plan(gridSize, gridSize, FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);

    for (i = 0; i < gridSize * gridSize; i++)                      //Initialize data structures to 0
    { vx[i] = vy[i] = vx0[i] = vy0[i] = fx[i] = fy[i] = rho[i] = rho0[i] = 0.0f; }
}

//FFT: Execute the Fast Fourier Transform on the dataset 'vx'.
//     'dirfection' indicates if we do the direct (1) or inverse (-1) Fourier Transform
void simulationRealization::FFT(int direction,void* vx)
{
    if(direction==1) rfftwnd_one_real_to_complex(plan_rc,(fftw_real*)vx,(fftw_complex*)vx);
    else             rfftwnd_one_complex_to_real(plan_cr,(fftw_complex*)vx,(fftw_real*)vx);
}

int simulationRealization::clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float simulationRealization::max(float x, float y)
{
    return x < y ? x : y;
}

//solve: Solve (compute) one step of the fluid flow simulation
void simulationRealization::solve(int grid_size, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt)
{
    fftw_real x, y, x0, y0, f, r, U[2], V[2], s, t;
    int i, j, i0, j0, i1, j1;

    for (i=0;i<grid_size * grid_size;i++)
    { vx[i] += dt*vx0[i]; vx0[i] = vx[i]; vy[i] += dt*vy0[i]; vy0[i] = vy[i]; }

    for ( x=0.5f / grid_size,i=0 ; i<grid_size ; i++,x+=1.0f/grid_size )
       for ( y=0.5f/grid_size,j=0 ; j<grid_size ; j++,y+=1.0f/grid_size )
       {
          x0 = grid_size*(x-dt*vx0[i+grid_size*j])-0.5f;
          y0 = grid_size*(y-dt*vy0[i+grid_size*j])-0.5f;
          i0 = clamp(x0); s = x0-i0;
          i0 = (grid_size+(i0%grid_size))%grid_size;
          i1 = (i0+1)%grid_size;
          j0 = clamp(y0); t = y0-j0;
          j0 = (grid_size+(j0%grid_size))%grid_size;
          j1 = (j0+1)%grid_size;
          vx[i+grid_size*j] = (1-s)*((1-t)*vx0[i0+grid_size*j0]+t*vx0[i0+grid_size*j1])+s*((1-t)*vx0[i1+grid_size*j0]+t*vx0[i1+grid_size*j1]);
          vy[i+grid_size*j] = (1-s)*((1-t)*vy0[i0+grid_size*j0]+t*vy0[i0+grid_size*j1])+s*((1-t)*vy0[i1+grid_size*j0]+t*vy0[i1+grid_size*j1]);
       }

    for(i=0; i<grid_size; i++)
      for(j=0; j<grid_size; j++)
      {  vx0[i+(grid_size+2)*j] = vx[i+grid_size*j]; vy0[i+(grid_size+2)*j] = vy[i+grid_size*j]; }

    FFT(1,vx0);
    FFT(1,vy0);

    for (i=0;i<=grid_size;i+=2)
    {
       x = 0.5f*i;
       for (j=0;j<grid_size;j++)
       {
          y = j<=grid_size/2 ? (fftw_real)j : (fftw_real)j-grid_size;
          r = x*x+y*y;
          if ( r==0.0f ) continue;
          f = (fftw_real)exp(-r*dt*visc);
          U[0] = vx0[i  +(grid_size+2)*j]; V[0] = vy0[i  +(grid_size+2)*j];
          U[1] = vx0[i+1+(grid_size+2)*j]; V[1] = vy0[i+1+(grid_size+2)*j];

          vx0[i  +(grid_size+2)*j] = f*((1-x*x/r)*U[0]     -x*y/r *V[0]);
          vx0[i+1+(grid_size+2)*j] = f*((1-x*x/r)*U[1]     -x*y/r *V[1]);
          vy0[i+  (grid_size+2)*j] = f*(  -y*x/r *U[0] + (1-y*y/r)*V[0]);
          vy0[i+1+(grid_size+2)*j] = f*(  -y*x/r *U[1] + (1-y*y/r)*V[1]);
       }
    }

    FFT(-1,vx0);
    FFT(-1,vy0);

    f = 1.0/(grid_size*grid_size);
    for (i=0;i<grid_size;i++)
       for (j=0;j<grid_size;j++)
       { vx[i+grid_size*j] = f*vx0[i+(grid_size+2)*j]; vy[i+grid_size*j] = f*vy0[i+(grid_size+2)*j]; }
}

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

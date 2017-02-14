#include "simulationrealization.h"
#include <QDebug>
#include <QPoint>
#include <QPointF>

SimulationRealization::SimulationRealization(Settings* settings, int gridSize):
    DIM(50), dt(0.4), visc(0.001),
    color_dir(0), vec_scale(1000), draw_smoke(0), draw_vecs(1),
    COLOR_BLACKWHITE(0), COLOR_RAINBOW(1), COLOR_BANDS(2),
    scalar_col(0), frozen(0)
{
    this->settings = settings;

    qDebug() << "SimulationRealization::SimulationRealization(int gridSize)";

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
void SimulationRealization::FFT(int direction,void* vx)
{
    if(direction==1) rfftwnd_one_real_to_complex(plan_rc,(fftw_real*)vx,(fftw_complex*)vx);
    else             rfftwnd_one_complex_to_real(plan_cr,(fftw_complex*)vx,(fftw_real*)vx);
}

int SimulationRealization::clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float SimulationRealization::max(float x, float y)
{
    return x > y ? x : y;
}

int SimulationRealization::arrayIndexCursorLocation(QPoint currentMousePosition)
{
    // Compute the array index that corresponds to the cursor location
    int xi = (int)clamp((double)(this->settings->simulation->dimension + 1) * ((double)currentMousePosition.x()/ (double)this->settings->canvas->width));
    int yi = (int)clamp((double)(this->settings->simulation->dimension + 1) * ((double)currentMousePosition.y() / (double)this->settings->canvas->height));

    //Bound array index to canvas dimensions
    if (xi > (this->settings->simulation->dimension - 1))
        xi = this->settings->simulation->dimension - 1;
    if (yi > (this->settings->simulation->dimension - 1))
        yi = this->settings->simulation->dimension - 1;
    if (xi < 0)
        xi = 0;
    if (yi < 0)
        yi = 0;

    return yi * this->settings->simulation->dimension + xi;
}


int SimulationRealization::addForceAt(QPoint currentMousePosition, QPoint oldMousePosition )
{

    QPointF mouseDiff = QPointF(currentMousePosition - oldMousePosition);
    double length = sqrt(QPointF::dotProduct(mouseDiff, mouseDiff));

    if (length != 0.0f )
    {
        mouseDiff *= 0.1f/length;
    }

    int idx = arrayIndexCursorLocation(currentMousePosition);
    fx[idx] += mouseDiff.x();
    fy[idx] += mouseDiff.y();
    rho[idx] = 10.0f;
}

//solve: Solve (compute) one step of the fluid flow simulation
void SimulationRealization::solve(int grid_size, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt)
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

// diffuse_matter: This function diffuses matter that has been placed in the velocity field. It's almost identical to the
// velocity diffusion step in the function above. The input matter densities are in rho0 and the result is written into rho.
void SimulationRealization::diffuse_matter(int gride_size, fftw_real *vx, fftw_real *vy, fftw_real *rho, fftw_real *rho0, fftw_real dt)
{
    fftw_real x, y, x0, y0, s, t;
    int i, j, i0, j0, i1, j1;

    for ( x=0.5f/gride_size,i=0 ; i<gride_size ; i++,x+=1.0f/gride_size )
        for ( y=0.5f/gride_size,j=0 ; j<gride_size ; j++,y+=1.0f/gride_size )
        {
            x0 = gride_size*(x-dt*vx[i+gride_size*j])-0.5f;
            y0 = gride_size*(y-dt*vy[i+gride_size*j])-0.5f;
            i0 = clamp(x0);
            s = x0-i0;
            i0 = (gride_size+(i0%gride_size))%gride_size;
            i1 = (i0+1)%gride_size;
            j0 = clamp(y0);
            t = y0-j0;
            j0 = (gride_size+(j0%gride_size))%gride_size;
            j1 = (j0+1)%gride_size;
            rho[i+gride_size*j] = (1-s)*((1-t)*rho0[i0+gride_size*j0]+t*rho0[i0+gride_size*j1])+s*((1-t)*rho0[i1+gride_size*j0]+t*rho0[i1+gride_size*j1]);
        }
}

//set_forces: copy user-controlled forces to the force vectors that are sent to the solver.
//            Also dampen forces and matter density to get a stable simulation.
void SimulationRealization::set_forces(void)
{
    int i;
    for (i = 0; i < DIM * DIM; i++)
    {
        rho0[i]  = 0.995 * rho[i];
        fx[i] *= 0.85;
        fy[i] *= 0.85;
        vx0[i]    = fx[i];
        vy0[i]    = fy[i];
    }
}

//do_one_simulation_step: Do one complete cycle of the simulation:
//      - set_forces:
//      - solve:            read forces from the user
//      - diffuse_matter:   compute a new set of velocities
void SimulationRealization::do_one_simulation_step(void)
{
    if (!frozen)
    {
      set_forces();
      solve(DIM, vx, vy, vx0, vy0, visc, dt);
      diffuse_matter(DIM, vx, vy, rho, rho0, dt);
    }
}


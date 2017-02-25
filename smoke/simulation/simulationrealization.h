#ifndef SIMULATIONREALIZATION_H
#define SIMULATIONREALIZATION_H

#include "rfftw.h"
#include <math.h>
#include <QPoint>

class SimulationRealization
{
public:
    SimulationRealization();

    void addForceAt(QPoint newMousePosition, QPoint oldMousePosition);
    void do_one_simulation_step(void);

    //--- SIMULATION PARAMETERS ------------------------------------------------------------------------
    fftw_real *vx, *vy;             //(vx,vy)   = velocity field at the current moment
    fftw_real *rho, *rho0;			//smoke density at the current (rho) and previous (rho0) moment
    fftw_real *fx, *fy;	            //(fx,fy)   = user-controlled simulation forces, steered with the mouse

private:
    //--- SIMULATION PARAMETERS ------------------------------------------------------------------------
    double dt;				//simulation time step
    float visc;				//fluid viscosity
//    fftw_real *vx, *vy;             //(vx,vy)   = velocity field at the current moment
    fftw_real *vx0, *vy0;           //(vx0,vy0) = velocity field at the previous moment
    rfftwnd_plan plan_rc, plan_cr;  //simulation domain discretization


    //--- VISUALIZATION PARAMETERS ---------------------------------------------------------------------
    int   color_dir;            //use direction color-coding or not
    int   draw_smoke;           //draw the smoke or not
    int   draw_vecs;            //draw the vector field or not
    const int COLOR_BLACKWHITE;   //different types of color mapping: black-and-white, rainbow, banded
    const int COLOR_RAINBOW;
    const int COLOR_BANDS;
    int   scalar_col;           //method for scalar coloring


    void FFT(int direction,void* vx);
    void solve(int grid_size, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt);
    void diffuse_matter(int gride_size, fftw_real *vx, fftw_real *vy, fftw_real *rho, fftw_real *rho0, fftw_real dt);
    void set_forces(void);

};

#endif // SIMULATIONREALIZATION_H

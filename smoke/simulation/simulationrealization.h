#ifndef SIMULATIONREALIZATION_H
#define SIMULATIONREALIZATION_H

#include "rfftw.h"
#include <math.h>

class simulationRealization
{
public:
    simulationRealization(int gridSize = 50);

private:
    //--- SIMULATION PARAMETERS ------------------------------------------------------------------------
    const int DIM;				//size of simulation grid
    double dt;				//simulation time step
    float visc;				//fluid viscosity
    fftw_real *vx, *vy;             //(vx,vy)   = velocity field at the current moment
    fftw_real *vx0, *vy0;           //(vx0,vy0) = velocity field at the previous moment
    fftw_real *fx, *fy;	            //(fx,fy)   = user-controlled simulation forces, steered with the mouse
    fftw_real *rho, *rho0;			//smoke density at the current (rho) and previous (rho0) moment
    rfftwnd_plan plan_rc, plan_cr;  //simulation domain discretization


    //--- VISUALIZATION PARAMETERS ---------------------------------------------------------------------
    int   winWidth, winHeight;      //size of the graphics window, in pixels
    int   color_dir;            //use direction color-coding or not
    float vec_scale;			//scaling of hedgehogs
    int   draw_smoke;           //draw the smoke or not
    int   draw_vecs;            //draw the vector field or not
    const int COLOR_BLACKWHITE;   //different types of color mapping: black-and-white, rainbow, banded
    const int COLOR_RAINBOW;
    const int COLOR_BANDS;
    int   scalar_col;           //method for scalar coloring
    int   frozen;               //toggles on/off the animation
};

#endif // SIMULATIONREALIZATION_H

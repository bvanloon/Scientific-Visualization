#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "rfftw.h"

class SimulationData
{
   public:
      SimulationData(int dimension);
      ~SimulationData();

      fftw_real *vx, *vy;         //(vx,vy)   = velocity field at the current moment
      fftw_real *fx, *fy;         //(fx,fy)   = user-controlled simulation forces, steered with the mouse
      fftw_real *rho;             //smoke density at the current (rho) and previous (rho0) moment

private:
      void allocateVelocityData(int dimension);
      void allocteForceData(int dimension);
      void allocateDensityData(int dimension);
};

#endif // SIMULATIONDATA_H

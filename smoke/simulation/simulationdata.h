#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "rfftw.h"

class SimulationData
{
   public:
      SimulationData(int dimension);
      SimulationData(const SimulationData& obj);
      ~SimulationData();

      fftw_real *getVx() const;

      fftw_real *getVy() const;

      fftw_real *getFx() const;

      fftw_real *getFy() const;

      fftw_real *getRho() const;

   private:
      fftw_real *vx, *vy;         //(vx,vy)   = velocity field at the current moment
      fftw_real *fx, *fy;         //(fx,fy)   = user-controlled simulation forces, steered with the mouse
      fftw_real *rho;             //smoke density at the current (rho) and previous (rho0) moment

      size_t velocitiesSize;
      size_t rhoSize;
      size_t forceSize;

      void allocateVelocityData(int length);

      void allocteForceData(int length);

      void allocateDensityData(int dimension);
};

#endif // SIMULATIONDATA_H

#include "simulationdata.h"

SimulationData::SimulationData(int dimension)
{
   size_t mallocDimension = dimension * 2 * (dimension / 2 + 1) * sizeof(fftw_real);

   vx = (fftw_real *)malloc(mallocDimension);
   vy = (fftw_real *)malloc(mallocDimension);
   fx = (fftw_real *)malloc(mallocDimension);
   fy = (fftw_real *)malloc(mallocDimension);
   rho = (fftw_real *)malloc(mallocDimension);
}

SimulationData::~SimulationData()
{
   free(vx);
   free(vy);
   free(fx);
   free(fy);
   free(rho);
}

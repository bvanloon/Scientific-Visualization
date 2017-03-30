#include "simulationdata.h"

SimulationData::SimulationData(int dimension)
{
   allocateVelocityData(dimension);
   allocteForceData(dimension);
   allocateDensityData(dimension);
}

SimulationData::~SimulationData()
{
   free(vx);
   free(vy);
   free(fx);
   free(fy);
   free(rho);
}

void SimulationData::allocateVelocityData(int dimension)
{
   size_t mallocDimension = dimension * 2 * (dimension / 2 + 1) * sizeof(fftw_real);

   vx = (fftw_real *)malloc(mallocDimension);
   vy = (fftw_real *)malloc(mallocDimension);
}

void SimulationData::allocteForceData(int dimension)
{
   size_t mallocDimension = dimension * dimension * sizeof(fftw_real);

   fx = (fftw_real *)malloc(mallocDimension);
   fy = (fftw_real *)malloc(mallocDimension);
}

void SimulationData::allocateDensityData(int dimension)
{
   size_t mallocDimension = dimension * dimension * sizeof(fftw_real);

   rho = (fftw_real *)malloc(mallocDimension);
}

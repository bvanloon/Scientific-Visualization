#include "simulationdata.h"
#include <algorithm>

SimulationData::SimulationData(int dimension) :
   velocitiesSize(dimension * 2 * (dimension / 2 + 1)),
   rhoSize(dimension * dimension),
   forceSize(dimension * dimension)
{
   allocateVelocityData(velocitiesSize);
   allocteForceData(forceSize);
   allocateDensityData(rhoSize);
}

SimulationData::SimulationData(const SimulationData& obj) :
   velocitiesSize(obj.velocitiesSize),
   rhoSize(obj.rhoSize),
   forceSize(obj.forceSize)
{
   allocateVelocityData(velocitiesSize);
   allocteForceData(forceSize);
   allocateDensityData(rhoSize);

   memccpy(this->vx, obj.vx, this->velocitiesSize, this->velocitiesSize);
   memccpy(this->vy, obj.vy, this->velocitiesSize, this->velocitiesSize);

   memccpy(this->fx, obj.fx, this->forceSize, this->forceSize);
   memccpy(this->fy, obj.fy, this->forceSize, this->forceSize);

   memccpy(this->rho, obj.rho, this->rhoSize, this->rhoSize);
}

SimulationData::~SimulationData()
{
   free(vx);
   free(vy);
   free(fx);
   free(fy);
   free(rho);
}

fftw_real *SimulationData::getVx() const
{
   return vx;
}

fftw_real SimulationData::getVxAt(int idx) const
{
   return vx[idx];
}

fftw_real *SimulationData::getVy() const
{
   return vy;
}

fftw_real SimulationData::getVyAt(int idx) const
{
   return vy[idx];
}

fftw_real *SimulationData::getFx() const
{
   return fx;
}

fftw_real SimulationData::getFxAt(int idx) const
{
   return fx[idx];
}

fftw_real *SimulationData::getFy() const
{
   return fy;
}

fftw_real SimulationData::getFyAt(int idx) const
{
   return fy[idx];
}

fftw_real *SimulationData::getRho() const
{
   return rho;
}

fftw_real SimulationData::getRhoAt(int idx) const
{
   return rho[idx];
}

void SimulationData::allocateVelocityData(int length)
{
   size_t mallocDimension = length * sizeof(fftw_real);

   vx = (fftw_real *)malloc(mallocDimension);
   vy = (fftw_real *)malloc(mallocDimension);
}

void SimulationData::allocteForceData(int length)
{
   size_t mallocDimension = length * sizeof(fftw_real);

   fx = (fftw_real *)malloc(mallocDimension);
   fy = (fftw_real *)malloc(mallocDimension);
}

void SimulationData::allocateDensityData(int length)
{
   size_t mallocDimension = length * sizeof(fftw_real);

   rho = (fftw_real *)malloc(mallocDimension);
}

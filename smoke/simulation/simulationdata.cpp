#include "simulationdata.h"

SimulationData::SimulationData(int numSimulationVertices) :
   vx((fftw_real *)malloc(numSimulationVertices)),
   vy((fftw_real *)malloc(numSimulationVertices)),
   fx((fftw_real *)malloc(numSimulationVertices)),
   fy((fftw_real *)malloc(numSimulationVertices)),
   rho((fftw_real *)malloc(numSimulationVertices))
{}

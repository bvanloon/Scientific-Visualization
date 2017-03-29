#ifndef SIMULATIONSTATEGRID_H
#define SIMULATIONSTATEGRID_H

#include "grid/uniformgrid.h"

class SimulationStateGrid : public UniformGrid
{
   public:
      SimulationStateGrid(UniformGrid* currentSimulationState);
};

#endif // SIMULATIONSTATEGRID_H

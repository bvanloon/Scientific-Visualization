#include "simulationstategrid.h"

SimulationStateGrid::SimulationStateGrid(UniformGrid *currentSimulationState) :
   UniformGrid(currentSimulationState->getDimension(),
               currentSimulationState->getCellSize(),
               true,
               currentSimulationState->getPadding())
{}

#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"
#include "grid/simulationgrid.h"
#include "unused.h"

class SmokeEngine : public AbstractEngine
{
   public:
      SmokeEngine(SimulationGrid* grid);

      virtual void draw(Simulation *simulation);

   private:
      SimulationGrid* simulation;

      int fillBuffers(Simulation *UNUSED(simulation));
};


#endif // SMOKEENGINE_H

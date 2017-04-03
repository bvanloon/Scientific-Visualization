#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"
#include "grid/simulationgrid.h"
#include "unused.h"

class SmokeEngine : public AbstractEngine
{
   public:
      SmokeEngine(SimulationGrid *grid);

      void draw();

   private:
      SimulationGrid *simulation;
};


#endif // SMOKEENGINE_H

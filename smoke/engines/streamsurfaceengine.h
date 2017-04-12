#ifndef STREAMSURFACEENGINE_H
#define STREAMSURFACEENGINE_H

#include "abstractengine.h"
#include "grid/simulationgrid.h"
#include "unused.h"

class StreamSurfaceEngine : public AbstractEngine
{
   public:
      StreamSurfaceEngine(SimulationGrid *grid);

      void draw();

   private:
      SimulationGrid *simulation;
};

#endif // STREAMSURFACEENGINE_H

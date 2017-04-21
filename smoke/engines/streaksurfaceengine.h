#ifndef STREAMSURFACEENGINE_H
#define STREAMSURFACEENGINE_H

#include "abstract3Dengine.h"
#include "grid/simulationgrid.h"
#include "streamobjects/streamsurface.h"
#include "unused.h"

class StreakSurfaceEngine : public Abstract3DEngine
{
   public:
      StreakSurfaceEngine(SimulationGrid *grid);

      void draw();

   private:
      SimulationGrid *simulation;

      void drawVertices(streamobject::Surface surface);
      void drawLines(streamobject::Surface surface);
      void drawSurface(streamobject::Surface surface);
};

#endif // STREAMSURFACEENGINE_H

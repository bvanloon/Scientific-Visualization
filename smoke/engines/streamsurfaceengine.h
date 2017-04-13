#ifndef STREAMSURFACEENGINE_H
#define STREAMSURFACEENGINE_H

#include "abstractengine.h"
#include "grid/simulationgrid.h"
#include "streamobjects/streamsurface.h"
#include "unused.h"

class StreamSurfaceEngine : public AbstractEngine
{
   public:
      StreamSurfaceEngine(SimulationGrid *grid);

      void draw();

   private:
      SimulationGrid *simulation;

      void drawVertices(streamobject::Surface surface);
      void drawLines(streamobject::Surface surface);
      void drawSurface(streamobject::Surface surface);
};

#endif // STREAMSURFACEENGINE_H

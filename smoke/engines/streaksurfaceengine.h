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

      void drawSurface(streamobject::Surface surface);
      void drawVertices(QList<streamobject::Line> streakLines);
      void drawLines(QList<streamobject::Line> streakLines);

      QList<QVector3D> getSeedPoints();

      QList<streamobject::Line> computeStreakLines(QList<QVector3D> seedPoints);

      double computeZStep();
};

#endif // STREAMSURFACEENGINE_H

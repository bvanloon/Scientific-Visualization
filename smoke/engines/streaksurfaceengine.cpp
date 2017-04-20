#include "streaksurfaceengine.h"

StreakSurfaceEngine::StreakSurfaceEngine(SimulationGrid *grid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight,
                  Settings::engines::EnginesTypes::streamSurfaces),
   simulation(grid)
{}

void StreakSurfaceEngine::draw()
{
   streamobject::Surface surface = streamobject::Surface::debugSurfaceWithSplit(2);
   drawSurface(surface);
   if (Settings::visualization::streakSurface().showLines) drawLines(surface);
   if (Settings::visualization::streakSurface().showVertices) drawVertices(surface);

   GPUData data = surface.GPUDataSurfaceEdges();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawVertices(streamobject::Surface surface)
{
   bool warningShown = false;
   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawVertices: Temporarily showing the seedpoints.";

   GPUData data(GL_POINTS);
   QList<QVector3D> seedPoints = Settings::visualization::streakSurface().seedCurve->getSeedPoints(Settings::visualization::streakSurface().resolution);
   for (QVector3D seedPoint : seedPoints)
   {
      data.addElement(seedPoint, QVector3D(0.0, 0.0, 1.0), 1.0, 1.0);
   }
//   GPUData data = surface.GPUDataVertices();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawLines(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataLines();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawSurface(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataSurface();
   updateBuffersAndDraw(data);
}

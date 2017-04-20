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
   if (Settings::visualization::streamSurfaces().showLines) drawLines(surface);
   if (Settings::visualization::streamSurfaces().showVertices) drawVertices(surface);

   GPUData data = surface.GPUDataSurfaceEdges();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawVertices(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataVertices();
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

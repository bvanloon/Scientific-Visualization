#include "streamsurfaceengine.h"

StreamSurfaceEngine::StreamSurfaceEngine(SimulationGrid *grid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight,
                  Settings::engines::EnginesTypes::streamSurfaces),
   simulation(grid)
{}

void StreamSurfaceEngine::draw()
{
   streamobject::Surface surface = streamobject::Surface::debugSurfaceWithSplit();
   drawSurface(surface);
   if (Settings::visualization::streamSurfaces().showLines) drawLines(surface);
   if (Settings::visualization::streamSurfaces().showVertices) drawVertices(surface);
}

void StreamSurfaceEngine::drawVertices(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataVertices();
   updateBuffersAndDraw(data);
}

void StreamSurfaceEngine::drawLines(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataLines();
   updateBuffersAndDraw(data);
}

void StreamSurfaceEngine::drawSurface(streamobject::Surface surface)
{
   GPUData data = surface.GPUDataSurface();
   updateBuffersAndDraw(data);
}

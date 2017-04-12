#include "streamsurfaceengine.h"

StreamSurfaceEngine::StreamSurfaceEngine(SimulationGrid *grid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight,
                  Settings::engines::EnginesTypes::streamSurfaces),
   simulation(grid)
{}

void StreamSurfaceEngine::draw()
{
   GPUData data = GPUData::debugSlice();
   updateBuffersAndDraw(data);
}

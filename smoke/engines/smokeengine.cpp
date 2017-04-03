#include "smokeengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/smokebuilder.h"

SmokeEngine::SmokeEngine(SimulationGrid *grid) :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::smoke),
   simulation(grid)
{}

void SmokeEngine::draw()
{
   SmokeBuilder builder = SmokeBuilder(this->simulation, colorMap->textureGetter);
   GPUData data = builder.getGPUData();
   updateBuffersAndDraw(data);
}

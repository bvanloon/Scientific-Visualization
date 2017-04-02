#include "smokeengine.h"
#include "grid/utilities/smokebuilder.h"
#include "settings/visualizationsettings.h"

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

int SmokeEngine::fillBuffers(Simulation *UNUSED(simulation))
{
   std::logic_error("SmokeEngine::fillBuffers is only implemented to ensure compliance with legacy code.");
   return 0;
}

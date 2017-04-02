#include "smokeengine.h"
#include "grid/utilities/smokebuilder.h"
#include "settings/visualizationsettings.h"

SmokeEngine::SmokeEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::smoke)
{}

void SmokeEngine::draw(Simulation *simulation)
{
   int bufferLength = this->fillBuffers(simulation);

   drawWithMode(GL_TRIANGLES, bufferLength);
}

int SmokeEngine::fillBuffers(Simulation *simulation)
{
   SmokeBuilder builder = SmokeBuilder(simulation->getSimulationGrid(), colorMap->textureGetter);
   GPUData data = builder.getGPUData();

   updateBuffers(data);
   return data.numElements();
}

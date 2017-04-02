#include "smokeslicesengine.h"
#include "grid/utilities/smokebuilder.h"
#include "settings/visualizationsettings.h"

SmokeSlicesEngine::SmokeSlicesEngine(SimulationGrid *grid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::smokeSlices),
   simulation(grid)
{
   connectToSettings();
}

void SmokeSlicesEngine::updateCache()
{
   SmokeBuilder builder = SmokeBuilder(this->simulation, colorMap->textureGetter);
   GPUData newData = builder.getGPUData();
   newData.transform(toSliceTransformation);

   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

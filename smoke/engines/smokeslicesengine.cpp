#include "smokeslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentsmokebuilder.h"

SmokeSlicesEngine::SmokeSlicesEngine(SimulationGrid *grid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::smokeSlices),
   simulation(grid)
{
   connectToSettings();
}

void SmokeSlicesEngine::updateCache()
{
   TranslucentSmokeBuilder builder(this->simulation, colorMap->textureGetter);
   GPUData newData = builder.getGPUData();
   newData.transform(toSliceTransformation);

   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

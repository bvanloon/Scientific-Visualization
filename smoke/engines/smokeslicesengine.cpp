#include "smokeslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentsmokebuilder.h"
#include "simulation/simulationstatehistory.h"

SmokeSlicesEngine::SmokeSlicesEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::smokeSlices)
{
   connectToSettings();
}

void SmokeSlicesEngine::updateCache()
{
   int idx = SimulationHistory::instance().mostRecentStateIdx();
   TranslucentSmokeBuilder builder(&SimulationHistory::instance().getSimulationGridAtQueueIdx(idx),
                                   colorMap->textureGetter,
                                   Settings::simulation().getRange(colorMap->scalar));
   GPUData newData = builder.getGPUData();
   newData.transform(toSliceTransformation);

   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

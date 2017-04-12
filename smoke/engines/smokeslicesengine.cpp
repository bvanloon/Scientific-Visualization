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
   TranslucentSmokeBuilder builder(&SimulationHistory::instance().getCombinedSimulationGridOfLastStates(
                                       Settings::visualization::slices().numStatesPerSlice,
                                       Settings::visualization::slices().combinationMethod),
                                   colorMap->textureGetter,
                                   Settings::simulation().getRange(colorMap->scalar));
   this->cache.enqueue(builder.getGPUData());
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

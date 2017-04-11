#include "smokeslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentsmokebuilder.h"
#include "simulation/simulationstatehistory.h"

SmokeSlicesEngine::SmokeSlicesEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::smokeSlices)
{
   connectToSettings();
   qDebug() << "SmokeSlicesEngine::SmokeSliceEngine(): fill the cache with debug data";
   this->cache.enqueue(GPUData::debugLowerLeftTriangle());
   this->cache.enqueue(GPUData::debugUpperLeftTriangle());
   this->cache.enqueue(GPUData::debugUpperRightTriangle());
   this->cache.enqueue(GPUData::debugLowerRightTriangle());
}

void SmokeSlicesEngine::updateCache()
{
//   TranslucentSmokeBuilder builder(&SimulationHistory::instance().getCombinedSimulationGridOfLastStates(
//                                       Settings::visualization::slices().numStatesPerSlice,
//                                       Settings::visualization::slices().combinationMethod),
//                                   colorMap->textureGetter,
//                                   Settings::simulation().getRange(colorMap->scalar));
//   GPUData newData = builder.getGPUData();
//   newData.transform(toSliceTransformation);

   clearCache();
   this->cache.enqueue(GPUData::debugLowerLeftTriangle());
   this->cache.enqueue(GPUData::debugUpperLeftTriangle());
   this->cache.enqueue(GPUData::debugUpperRightTriangle());
   this->cache.enqueue(GPUData::debugLowerRightTriangle());

   static bool warningShown = false;
   if (!warningShown++) qDebug() << "SmokeSlicesEngine::updateCache(): fill the cache with debug data";
   //   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

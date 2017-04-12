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
//   TranslucentSmokeBuilder builder(&SimulationHistory::instance().getCombinedSimulationGridOfLastStates(
//                                       Settings::visualization::slices().numStatesPerSlice,
//                                       Settings::visualization::slices().combinationMethod),
//                                   colorMap->textureGetter,
//                                   Settings::simulation().getRange(colorMap->scalar));
//   GPUData newData = builder.getGPUData();
//   newData.transform(toSliceTransformation);

   static bool warningShown = false;
   if (!warningShown++) qDebug() << "SmokeSlicesEngine::updateCache(): fill the cache with debug data";

   static int counter = 0;
   counter = (counter + 1) % 4;

   GPUData newData;

   switch (counter)
   {
   case (0):
      newData = GPUData::debugLowerLeftTriangle();
      break;

   case (1):
      newData = GPUData::debugUpperLeftTriangle();
      break;

   case (2):
      newData = GPUData::debugUpperRightTriangle();
      break;

   case (3):
      newData = GPUData::debugLowerRightTriangle();
      break;
   }

   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

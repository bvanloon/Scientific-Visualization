#include "smokeslicesengine.h"
#include "grid/utilities/smokebuilder.h"
#include "settings/visualizationsettings.h"

SmokeSlicesEngine::SmokeSlicesEngine(SimulationGrid *grid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::smokeSlices,
                       computeToSliceTransformation()),
   simulation(grid)
{
   connectToSettings();
}

void SmokeSlicesEngine::updateCache()
{
   SmokeBuilder builder = SmokeBuilder(this->simulation, colorMap->textureGetter);
   GPUData newData = builder.getGPUData();

   this->cache.enqueue(newData);
}

void SmokeSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::smoke(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

QMatrix4x4 SmokeSlicesEngine::computeToSliceTransformation()
{
    QMatrix4x4 transform;
    qDebug() << "SmokeSlicesEngine::computeToSliceTransformation";
    return transform;
}

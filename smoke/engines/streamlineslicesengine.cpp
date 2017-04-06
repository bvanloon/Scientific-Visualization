#include "streamlineslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentstreamlinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreamLineSlicesEngine::StreamLineSlicesEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::streamLineSlices)
{
   connectToSettings();
}

void StreamLineSlicesEngine::updateCache()
{
   GPUData newData = buildStreamLines();
   newData.transform(toSliceTransformation);

   this->cache.enqueue(newData);
}

GPUData StreamLineSlicesEngine::buildStreamLines()
{
   GPUData data(streamobject::Line::drawMode);

   int idx = SimulationHistory::instance().mostRecentStateIdx();

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(&SimulationHistory::instance().getSimulationGridAtQueueIdx(idx), seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineSlicesEngine::buildStreamLine(const SimulationGrid *grid, QPointF seedPoint)
{
   TranslucentStreamLineBuilder builder(grid, QVector3D(seedPoint),
                                        Settings::visualization::streamLines().vectorField,
                                        Settings::visualization::streamLines().colorMap->textureGetter,
                                        Settings::simulation().getMagnitudeRange(Settings::visualization::streamLines().vector));
   streamobject::Line streamLine = builder.getStreamLine();
   return streamLine.toGPUData();
}

void StreamLineSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::streamLines(), SIGNAL(clearCache()),
            this, SLOT(onClearCache()));
}

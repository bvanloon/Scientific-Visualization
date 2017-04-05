#include "streamlineslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentstreamlinebuilder.h"

StreamLineSlicesEngine::StreamLineSlicesEngine(UniformGrid *simulationGrid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::streamLineSlices),
   grid(simulationGrid)
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

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineSlicesEngine::buildStreamLine(QPointF seedPoint)
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

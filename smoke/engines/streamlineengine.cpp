#include "streamlineengine.h"
#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include "grid/utilities/streamlinebuilder.h"

StreamLineEngine::StreamLineEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::streamLines),
   grid(simulationGrid)
{}

int StreamLineEngine::fillBuffers()
{
   std::logic_error("AbstractSliceEngine::fillBuffers is only implemented to ensure compliance with legacy code.");
   return 0;
}

GPUData StreamLineEngine::buildStreamLines()
{
   GPUData data(streamobject::Line::drawMode);

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineEngine::buildStreamLine(QPointF seedPoint)
{
   StreamLineBuilder builder(grid, QVector3D(seedPoint),
                             Settings::visualization::streamLines().vectorField,
                             Settings::visualization::streamLines().colorMap->textureGetter);
   streamobject::Line streamLine = builder.getStreamLine();

   return streamLine.toGPUData();
}

void StreamLineEngine::draw()
{
   GPUData data = buildStreamLines();
   updateBuffersAndDraw(data);
}

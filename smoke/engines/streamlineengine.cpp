#include "streamlineengine.h"
#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"

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
   streamobject::Line streamLine = grid->computeStreamLine(QVector3D(seedPoint),
                                                           Settings::visualization::streamLines().colorMap->textureGetter,
                                                           Settings::visualization::streamLines().vectorField);
   return streamLine.toGPUData();
}

void StreamLineEngine::draw()
{
   GPUData data = buildStreamLines();
   updateBuffersAndDraw(data);
}

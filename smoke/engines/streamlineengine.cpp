#include "streamlineengine.h"
#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"

StreamLineEngine::StreamLineEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight),
   grid(simulationGrid)
{}

int StreamLineEngine::updateBuffers()
{
   GPUData data = buildStreamLines();

   AbstractEngine::updateBuffers(data);
   return data.numElements();
}

GPUData StreamLineEngine::buildStreamLines()
{
   GPUData data;

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      data.extend(buildStreamLine(seedpoint));
   }
   return data;
}

GPUData StreamLineEngine::buildStreamLine(QPointF seedPoint)
{
   streamobject::Line streamLine = streamobject::Line(seedPoint, 0.0);
   streamLine.addVertex(seedPoint + 2 * seedPoint, 0.0);

   GPUData data = streamLine.toGPUData();
   data.setTextureCoordinates(QVector<float>(2, 0.0));

   return data;
}

void StreamLineEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(this->drawMode, bufferLength);
}

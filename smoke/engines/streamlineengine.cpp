#include "streamlineengine.h"
#include "utilities/gpudata.h"
#include "shapes/polyline.h"

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
    for(QPointF seedpoint : Settings::visualization::streamLines().seedPoints){
        data.extend(buildStreamLine(seedpoint));
    }
    return data;
}

GPUData StreamLineEngine::buildStreamLine(QPointF seedPoint)
{
    shapes::PolyLine polyLine = shapes::PolyLine(seedPoint);
    polyLine.addVertex(seedPoint + 2 * seedPoint);

    GPUData data = polyLine.toGPUData();
    data.setTextureCoordinates(QVector<float>(2, 0.0));

    return data;
}


void StreamLineEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(this->drawMode, bufferLength);
}

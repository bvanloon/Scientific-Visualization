#include "streamlineengine.h"
#include "utilities/gpudata.h"

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
    GPUData data;
    QVector3D normal = QVector3D(0.0, 0.0, 1.0);
    data.addElement(QVector3D(seedPoint), normal, 0.0);
    data.addElement(QVector3D(seedPoint + 3 * QPointF(seedPoint)), normal, 0.0);
    return data;
}


void StreamLineEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(this->drawMode, bufferLength);
}

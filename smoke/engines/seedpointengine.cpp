#include "seedpointengine.h"
#include "shapes/rectangle.h"
#include "QMatrix4x4"

const double SeedPointEngine::lowValue = 0.0;
const double SeedPointEngine::highValue = 1.0;

SeedPointEngine::SeedPointEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::seedPoints)
{}

void SeedPointEngine::draw()
{
   GPUData data = buildGPUData();
   updateBuffersAndDraw(data);
}

GPUData SeedPointEngine::buildGPUData()
{
   GPUData data(GL_POINTS);
   QVector3D normal = QVector3D(0.0, 0.0, 1.0);
   for (QPointF seedPoint : Settings::visualization::streamLines().seedPoints)
   {
      data.addElement(QVector3D(seedPoint), normal, highValue);
   }
   return data;
}

void SeedPointEngine::setColorMapValueRange(float UNUSED(min), float UNUSED(max))
{
   AbstractEngine::setColorMapClampingTo(false);
}

void SeedPointEngine::setColorMapClampingTo(bool UNUSED(clampingOn))
{
   AbstractEngine::setColorMapValueRange(lowValue, highValue);
}

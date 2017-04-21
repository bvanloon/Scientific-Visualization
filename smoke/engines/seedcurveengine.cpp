#include "seedcurveengine.h"

SeedCurveEngine::SeedCurveEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::seedCurve)
{}

void SeedCurveEngine::draw()
{
   drawEdges();
   drawVertices();
}

void SeedCurveEngine::drawEdges()
{
   int resolution = Settings::visualization::streakSurface().resolution;
   GPUData data = Settings::visualization::streakSurface().seedCurve->GPUDataEdges(resolution);
   updateBuffersAndDraw(data);
}

void SeedCurveEngine::drawVertices()
{
   GPUData data = Settings::visualization::streakSurface().seedCurve->GPUDataVertices();
   updateBuffersAndDraw(data);
}

void SeedCurveEngine::setColorMapClampingTo(bool UNUSED(clampingOn))
{
   AbstractEngine::setColorMapClampingTo(false);
}

void SeedCurveEngine::setColorMapValueRange(float UNUSED(min), float UNUSED(max))
{
   AbstractEngine::setColorMapValueRange(0.0, 1.0);
}

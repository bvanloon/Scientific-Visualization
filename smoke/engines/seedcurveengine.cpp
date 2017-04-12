#include "seedcurveengine.h"

SeedCurveEngine::SeedCurveEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::seedCurves)
{}

void SeedCurveEngine::draw()
{
   updateBuffersAndDraw(GPUData::debugSlice());
}

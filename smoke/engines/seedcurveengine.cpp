#include "seedcurveengine.h"

SeedCurveEngine::SeedCurveEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::seedCurves)
{}

void SeedCurveEngine::draw()
{
   GPUData data = GPUData::debugSlice();
   updateBuffers(data);
}

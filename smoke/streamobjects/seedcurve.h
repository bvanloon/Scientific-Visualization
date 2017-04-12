#ifndef SEEDCURVE_H
#define SEEDCURVE_H

#include "shapes/polyline.h"
#include "utilities/gpudata.h"

class SeedCurve : public shapes::PolyLine
{
   public:
      SeedCurve();

      GPUData toGPUData(float textureCoordinate, float alpha = 1.0);

      void applyTransformation(QMatrix4x4 transform);
};

#endif // SEEDCURVE_H

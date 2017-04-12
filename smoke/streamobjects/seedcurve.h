#ifndef SEEDCURVE_H
#define SEEDCURVE_H

#include "shapes/polyline.h"
#include "utilities/gpudata.h"

class SeedCurve : public shapes::PolyLine
{
   public:
      SeedCurve();

      GPUData toGPUData(int resolution);

      void applyTransformation(QMatrix4x4 transform);

   private:
      GPUData edgeToGPUData(QVector3D start, QVector3D end, int resolution);
};

#endif // SEEDCURVE_H

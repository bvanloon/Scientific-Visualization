#ifndef SEEDCURVE_H
#define SEEDCURVE_H

#include "shapes/polyline.h"
#include "utilities/gpudata.h"

class SeedCurve : public shapes::PolyLine
{
   public:
      SeedCurve();

      GPUData GPUDataEdges(int resolution);
      GPUData GPUDataVertices();

      void applyTransformation(QMatrix4x4 transform);

      QList<QVector3D> getSeedPoints(int resolution);

   private:
      GPUData edgeToGPUData(QVector3D start, QVector3D end, int resolution);

      QList<QVector3D> edgeToSeedPoints(QVector3D start, QVector3D end, int resolution);
};

#endif // SEEDCURVE_H

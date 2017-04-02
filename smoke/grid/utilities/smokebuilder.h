#ifndef SMOKEBUILDER_H
#define SMOKEBUILDER_H

#include "utilities/gpudata.h"
#include "grid/vertex.h"
#include "grid/simulationgrid.h"

class SmokeBuilder
{
   public:
      SmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter);

      GPUData getGPUData() const;

private:
      SimulationGrid *grid;
      Vertex::scalarGetter textureGetter;
      GPUData data;
      QVector3D normal;

      void build();
      void addVertex(Vertex *vertex);
};

#endif // SMOKEBUILDER_H

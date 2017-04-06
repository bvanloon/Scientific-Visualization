#ifndef SMOKEBUILDER_H
#define SMOKEBUILDER_H

#include "utilities/gpudata.h"
#include "grid/vertex.h"
#include "grid/simulationgrid.h"

class SmokeBuilder
{
   public:
      SmokeBuilder(const SimulationGrid *grid, Vertex::scalarGetter textureGetter);

      GPUData getGPUData();

   protected:
      GPUData data;
      Vertex::scalarGetter getTextureCoordinate;
      QVector3D normal;
      const SimulationGrid *grid;

      void build();
      virtual void addVertex(Vertex *vertex);
};

#endif // SMOKEBUILDER_H

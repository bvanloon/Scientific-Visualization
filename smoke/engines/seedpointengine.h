#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include "abstractengine.h"
#include "unused.h"
#include "utilities/mesh.h"
#include "utilities/gpudata.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();

      void draw();

   private:
      GPUData buildGPUData();

      void setColorMapClampingTo(bool UNUSED(clampingOn));
      void setColorMapValueRange(float UNUSED(min), float UNUSED(max));

      static const double lowValue;
      static const double highValue;
};

#endif // SEEDPOINTENGINE_H

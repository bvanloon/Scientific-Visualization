#ifndef TRANSLUCENTSMOKEBUILDER_H
#define TRANSLUCENTSMOKEBUILDER_H

#include "abstracttranslucentbuilder.h"
#include "smokebuilder.h"

class TranslucentSmokeBuilder :
   private AbstractTranslucentBuilder,
   public SmokeBuilder
{
   public:
      TranslucentSmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter);
};

#endif // TRANSLUCENTSMOKEBUILDER_H

#ifndef TRANSLUCENTSMOKEBUILDER_H
#define TRANSLUCENTSMOKEBUILDER_H

#include "abstracttranslucentbuilder.h"
#include "smokebuilder.h"

class TranslucentSmokeBuilder :
   private AbstractTranslucentBuilder,
   public SmokeBuilder
{
   public:
      TranslucentSmokeBuilder(const SimulationGrid *grid,
                              Vertex::scalarGetter getTextureCoordinate,
                              Range<double> textureRange);

   protected:
      void addVertex(Vertex *vertex);
};

#endif // TRANSLUCENTSMOKEBUILDER_H

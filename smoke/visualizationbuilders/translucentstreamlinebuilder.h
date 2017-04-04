#ifndef TRANSLUCENTSTREAMLINEBUILDER_H
#define TRANSLUCENTSTREAMLINEBUILDER_H

#include "abstracttranslucentbuilder.h"
#include "streamlinebuilder.h"

class TranslucentStreamLineBuilder :
   private AbstractTranslucentBuilder,
   public StreamLineBuilder
{
   public:
      TranslucentStreamLineBuilder(UniformGrid *grid,
                                   QVector3D currentPosition,
                                   Vertex::vectorGetter vectorGetter,
                                   Vertex::scalarGetter magnitudeGetter,
                                   Range magnitudeRange);
};

#endif // TRANSLUCENTSTREAMLINEBUILDER_H

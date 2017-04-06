#ifndef TRANSLUCENTSTREAMLINEBUILDER_H
#define TRANSLUCENTSTREAMLINEBUILDER_H

#include "abstracttranslucentbuilder.h"
#include "streamlinebuilder.h"

class TranslucentStreamLineBuilder :
   private AbstractTranslucentBuilder,
   public StreamLineBuilder
{
   public:
      TranslucentStreamLineBuilder(const UniformGrid *grid,
                                   QVector3D currentPosition,
                                   Vertex::vectorGetter vectorGetter,
                                   Vertex::scalarGetter magnitudeGetter,
                                   Range<double> magnitudeRange);

   private:
      bool tryAddingVertex(QVector3D position);
};

#endif // TRANSLUCENTSTREAMLINEBUILDER_H

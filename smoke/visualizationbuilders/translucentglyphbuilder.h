#ifndef TRANSLUCENTGLYPHBUILDER_H
#define TRANSLUCENTGLYPHBUILDER_H

#include "abstracttranslucentbuilder.h"
#include "glyphbuilder.h"

class TranslucentGlyphBuilder :
   private AbstractTranslucentBuilder,
   public GlyphBuilder
{
   public:
      TranslucentGlyphBuilder(UniformGrid *grid,
                              Settings::sim::GlyphsType glyphThype,
                              Vertex::scalarGetter getTextureCoordinate,
                              Vertex::vectorGetter directionGetter,
                              Range magnitudeRange);

   private:
};

#endif // TRANSLUCENTGLYPHBUILDER_H

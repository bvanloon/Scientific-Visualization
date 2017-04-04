#include "translucentglyphbuilder.h"

TranslucentGlyphBuilder::TranslucentGlyphBuilder(UniformGrid *grid, Settings::sim::GlyphsType glyphThype, Vertex::scalarGetter getTextureCoordinate, Vertex::vectorGetter directionGetter, Range magnitudeRange) :
   AbstractTranslucentBuilder(magnitudeRange),
   GlyphBuilder(grid,
                glyphThype,
                getTextureCoordinate,
                directionGetter)
{}

#include "translucentglyphbuilder.h"

TranslucentGlyphBuilder::TranslucentGlyphBuilder(UniformGrid *grid, Settings::sim::GlyphsType glyphThype, Vertex::scalarGetter getTextureCoordinate, Vertex::vectorGetter directionGetter, Range magnitudeRange) :
   AbstractTranslucentBuilder(magnitudeRange),
   GlyphBuilder(grid,
                glyphThype,
                getTextureCoordinate,
                directionGetter)
{}

GPUData TranslucentGlyphBuilder::buildHedgeHog(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   HedgeHog hedgeHog = HedgeHog(*(vertex->getPosition()),
                                (vertex->*(getDirection))());
   return hedgeHog.toGPUData(textureCoordinate);
}

GPUData TranslucentGlyphBuilder::buildTriangle(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Triangle triangle = Triangle(*(vertex->getPosition()),
                                (vertex->*(getDirection))());
   return triangle.toGPUData(textureCoordinate);
}

GPUData TranslucentGlyphBuilder::buildAirplane(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Airplane triangle = Airplane(*(vertex->getPosition()),
                                (vertex->*(getDirection))());
   return triangle.toGPUData(textureCoordinate);
}

GPUData TranslucentGlyphBuilder::buildCone(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Cone cone = Cone(*(vertex->getPosition()),
                    (vertex->*(getDirection))());
   return cone.toGPUData(textureCoordinate);
}

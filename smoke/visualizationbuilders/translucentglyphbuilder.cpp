#include "translucentglyphbuilder.h"

TranslucentGlyphBuilder::TranslucentGlyphBuilder(UniformGrid *grid,
                                                 Settings::sim::GlyphsType glyphThype,
                                                 Vertex::scalarGetter textureGetter,
                                                 Vertex::vectorGetter directionGetter,
                                                 Vertex::scalarGetter alphaGetter,
                                                 Range<double> unNormalizedAlphaRange) :
   AbstractTranslucentBuilder(unNormalizedAlphaRange),
   GlyphBuilder(grid,
                glyphThype,
                textureGetter,
                directionGetter),
   getUnNormalizedAlphaValue(alphaGetter)
{}

float TranslucentGlyphBuilder::computeAlpha(Vertex *vertex) const
{
   float value = (vertex->*(getUnNormalizedAlphaValue))();
   return AbstractTranslucentBuilder::computeAlpha(value);
}

GPUData TranslucentGlyphBuilder::buildHedgeHog(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(vertex);
   HedgeHog hedgeHog = HedgeHog(*(vertex->getPosition()), direction);
   return hedgeHog.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildTriangle(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(vertex);
   Triangle triangle = Triangle(*(vertex->getPosition()), direction);
   return triangle.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildAirplane(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(vertex);
   Airplane triangle = Airplane(*(vertex->getPosition()), direction);
   return triangle.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildCone(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(vertex);
   Cone cone = Cone(*(vertex->getPosition()), direction);
   return cone.toGPUData(textureCoordinate, alpha);
}

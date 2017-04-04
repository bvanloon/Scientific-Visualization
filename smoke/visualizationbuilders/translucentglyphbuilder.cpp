#include "translucentglyphbuilder.h"

TranslucentGlyphBuilder::TranslucentGlyphBuilder(UniformGrid *grid, Settings::sim::GlyphsType glyphThype, Vertex::scalarGetter getTextureCoordinate, Vertex::vectorGetter directionGetter, Range<double> magnitudeRange) :
   AbstractTranslucentBuilder(magnitudeRange),
   GlyphBuilder(grid,
                glyphThype,
                getTextureCoordinate,
                directionGetter)
{}

float TranslucentGlyphBuilder::computeAlpha(QVector3D vector) const
{
   float magnitude = vector.length();
   return AbstractTranslucentBuilder::computeAlpha(magnitude);
}

GPUData TranslucentGlyphBuilder::buildHedgeHog(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(direction);
   HedgeHog hedgeHog = HedgeHog(*(vertex->getPosition()), direction);
   return hedgeHog.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildTriangle(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(direction);
   Triangle triangle = Triangle(*(vertex->getPosition()), direction);
   return triangle.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildAirplane(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(direction);
   Airplane triangle = Airplane(*(vertex->getPosition()), direction);
   return triangle.toGPUData(textureCoordinate, alpha);
}

GPUData TranslucentGlyphBuilder::buildCone(Vertex *vertex) const
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   QVector3D direction = (vertex->*(getDirection))();
   float alpha = computeAlpha(direction);
   Cone cone = Cone(*(vertex->getPosition()), direction);
   return cone.toGPUData(textureCoordinate, alpha);
}

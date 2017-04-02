#include "glyphbuilder.h"
#include "glyphs/abstractglyph.h"
#include "glyphs/glyphs.h"

GlyphBuilder::GlyphBuilder(UniformGrid *grid,
                           Settings::sim::GlyphsType glyphThype,
                           Vertex::scalarGetter textureGetter,
                           Vertex::vectorGetter directionGetter) :
   grid(grid),
   getTextureCoordinate(textureGetter),
   getDirection(directionGetter),
   data(build(glyphThype))
{}

GlyphBuilder::~GlyphBuilder()
{}

GPUData GlyphBuilder::getData() const
{
   return data;
}

GPUData GlyphBuilder::build(Settings::sim::GlyphsType glyphType)
{
   switch (glyphType)
   {
   case Settings::sim::GlyphsType::hedgehog:
      return buildHedgeHodges();

   case Settings::sim::GlyphsType::triangles:
      return buildTriangles();

   case Settings::sim::GlyphsType::airplane:
      return buildAirplanes();

   case Settings::sim::GlyphsType::cone:
      return buildCones();
   }
}

GPUData GlyphBuilder::buildHedgeHodges()
{
   return GPUData::debugSlice();
}

GPUData GlyphBuilder::buildTriangles()
{
   GPUData triangleData(GL_TRIANGLES);
   for (Vertex *vertex : grid->getVertices()) triangleData.extend(buildTriangle(vertex));
   return triangleData;
}

GPUData GlyphBuilder::buildTriangle(Vertex *vertex)
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Triangle triangle = Triangle(*(vertex->getPosition()),
                                (vertex->*(getDirection))(), textureCoordinate);
   return triangle.toGPUData(textureCoordinate);
}

GPUData GlyphBuilder::buildAirplanes()
{
   return GPUData::debugSlice();
}

GPUData GlyphBuilder::buildCones()
{
   GPUData cones(GL_TRIANGLES);
   for (Vertex *vertex : grid->getVertices()) cones.extend(buildCone(vertex));
   return cones;
}

GPUData GlyphBuilder::buildCone(Vertex *vertex)
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Cone cone = Cone(*(vertex->getPosition()),
                    (vertex->*(getDirection))(), textureCoordinate);
   return cone.toGPUData(textureCoordinate);
}

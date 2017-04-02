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
      return buildHedgeHogs();

   case Settings::sim::GlyphsType::triangles:
      return buildTriangles();

   case Settings::sim::GlyphsType::airplane:
      return buildAirplanes();

   case Settings::sim::GlyphsType::cone:
      return buildCones();
   }
}

GPUData GlyphBuilder::buildHedgeHogs()
{
   GPUData hedgeHodgeData(GL_LINES);
   for (Vertex *vertex : grid->getVertices()) hedgeHodgeData.extend(buildHedgeHog(vertex));
   return hedgeHodgeData;
}

GPUData GlyphBuilder::buildHedgeHog(Vertex *vertex)
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   HedgeHog hedgeHog = HedgeHog(*(vertex->getPosition()),
                                (vertex->*(getDirection))(), textureCoordinate);
   return hedgeHog.toGPUData(textureCoordinate);
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
    GPUData airplanes(GL_TRIANGLES);
    for (Vertex *vertex : grid->getVertices()) airplanes.extend(buildAirplane(vertex));
    return airplanes;
}

GPUData GlyphBuilder::buildAirplane(Vertex *vertex)
{
   float textureCoordinate = (vertex->*(getTextureCoordinate))();
   Airplane triangle = Airplane(*(vertex->getPosition()),
                                (vertex->*(getDirection))(), textureCoordinate);
   return triangle.toGPUData(textureCoordinate);
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

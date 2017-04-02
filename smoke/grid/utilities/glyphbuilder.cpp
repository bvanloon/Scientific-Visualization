#include "glyphbuilder.h"

GlyphBuilder::GlyphBuilder(UniformGrid *grid, Settings::sim::GlyphsType glyphThype) :
   grid(grid)
{
   this->data = build(glyphThype);
}

GlyphBuilder::~GlyphBuilder()
{
   qDebug() << "GlyphBuilder::~GlyphBuilder";
   delete data;
}

GPUData *GlyphBuilder::build(Settings::sim::GlyphsType glyphType)
{
   switch (glyphType)
   {
   case Settings::sim::GlyphsType::hedgehog:
      return buildHedgeHodgs();

   case Settings::sim::GlyphsType::triangles:
      return buildTriangles();

   case Settings::sim::GlyphsType::airplane:
      return buildAirplanes();

   case Settings::sim::GlyphsType::cone:
      return buildCones();
   }
}

GPUData *GlyphBuilder::buildHedgeHodgs()
{
   GPUData *data = new GPUData(GL_LINES);
   return data;
}

GPUData *GlyphBuilder::buildTriangles()
{
   GPUData *data = new GPUData(GL_TRIANGLES);
   return data;
}

GPUData *GlyphBuilder::buildAirplanes()
{
   GPUData *data = new GPUData(GL_TRIANGLES);
   return data;
}

GPUData *GlyphBuilder::buildCones()
{
   GPUData *data = new GPUData(GL_TRIANGLES);
   return data;
}

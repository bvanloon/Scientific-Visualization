#include "glyphsfactory.h"
#include "glyphs/hedgehog.h"
#include "glyphs/triangle.h"

#include <QDebug>

GlyphsFactory::GlyphsFactory()
{}

GlyphsTriangulation GlyphsFactory::createGlyphs(GlyphData data, GlyphsFactory::glyphs glypType)
{
   switch (glypType)
   {
   case GlyphsFactory::glyphs::hedgehog:
      return createHedgehogs(data);

      break;

   case GlyphsFactory::glyphs::triangles:
      return createTriangles(data);

      break;

   default:
      return GlyphsTriangulation();
   }
}

GlyphsTriangulation GlyphsFactory::createHedgehogs(GlyphData data)
{
   GlyphsTriangulation triangulation;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = HedgeHog(data.getPositions().at(i),
                                            data.getDirections().at(i),
                                            data.getTextureCoordinates().at(i));
      triangulation.extend(currentGlyph);
   }
   return triangulation;
}

GlyphsTriangulation GlyphsFactory::createTriangles(GlyphData data)
{
   GlyphsTriangulation triangulation;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = Triangle(data.getPositions().at(i),
                                             data.getDirections().at(i),
                                             data.getTextureCoordinates().at(i));
      triangulation.extend(currentGlyph);
   }
   return triangulation;
}

QStringList GlyphsFactory::getGlyphsNames()
{
   QStringList glyphsNamesList;

   glyphsNamesList << "Hedgehogs" << "Triangles";

   return glyphsNamesList;
}

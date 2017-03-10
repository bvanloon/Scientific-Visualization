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

   default:
      return GlyphsTriangulation();
   }
}

GlyphsTriangulation GlyphsFactory::createHedgehogs(GlyphData data)
{
   GlyphsTriangulation glyphTriangles;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = HedgeHog(data.getPositions().at(i),
                                            data.getVectors().at(i),
                                            data.getScalars().at(i));
      glyphTriangles.extend(currentGlyph);
   }
   return glyphTriangles;
}

QStringList GlyphsFactory::getGlyphsNames()
{
   QStringList glyphsNamesList;

   glyphsNamesList << "hedgehog ";

   return glyphsNamesList;
}

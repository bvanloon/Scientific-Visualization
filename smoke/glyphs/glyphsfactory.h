#ifndef GLYPHSFACTORY_H
#define GLYPHSFACTORY_H

#include <QStringList>

#include "glyphs/abstractglyph.h"
#include "glyphstriangulation.h"
#include "grid/glyphdata.h"
#include "settings/settings.h"

class GlyphsFactory
{
   public:
//      enum glyphs
//      {
//         hedgehog,
//         triangles,
//         airplane
//      };


      static QStringList getGlyphsNames();

      GlyphsFactory();

      GlyphsTriangulation createGlyphs(GlyphData data, Settings::sim::GlyphsType glypType);

   private:
      GlyphsTriangulation createHedgehogs(GlyphData data);

      GlyphsTriangulation createTriangles(GlyphData data);

      GlyphsTriangulation createAirplanes(GlyphData data);

      GlyphsTriangulation createCones(GlyphData data);
};

#endif // GLYPHSFACTORY_H

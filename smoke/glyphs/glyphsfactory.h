#ifndef GLYPHSFACTORY_H
#define GLYPHSFACTORY_H

#include <QStringList>

#include "glyphs/abstractglyph.h"
#include "glyphstriangulation.h"
#include "grid/glyphdata.h"

class GlyphsFactory
{
   public:
      enum glyphs
      {
         hedgehog
      };


      static QStringList getGlyphsNames();

      GlyphsFactory();

      GlyphsTriangulation createGlyphs(GlyphData data, GlyphsFactory::glyphs glypType);

   private:
      GlyphsTriangulation createHedgehogs(GlyphData data);
};

#endif // GLYPHSFACTORY_H

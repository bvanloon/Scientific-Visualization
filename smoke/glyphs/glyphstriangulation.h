#ifndef GLYPHSTRIANGULATION_H
#define GLYPHSTRIANGULATION_H

#include <QVector>
#include <QVector3D>

#include "glyphs/abstractglyph.h"
class GlyphsTriangulation
{
   public:
      GlyphsTriangulation();

      void extend(AbstractGlyph glyph);

      QVector<QVector3D> getVertices() const;

      QVector<float> getTextureCoordinates() const;

   private:
      QVector<QVector3D> vertices;
      QVector<float> textureCoordinates;
};

#endif // GLYPHSTRIANGULATION_H

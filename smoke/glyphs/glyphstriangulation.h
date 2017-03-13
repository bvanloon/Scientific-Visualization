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

      QVector<QVector3D> getNormals() const;

private:
      QVector<QVector3D> vertices;
      QVector<float> textureCoordinates;
      QVector<QVector3D> normals;
};

#endif // GLYPHSTRIANGULATION_H

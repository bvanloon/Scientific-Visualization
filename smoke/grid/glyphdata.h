#ifndef GLYPHDATA_H
#define GLYPHDATA_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>

class GlyphData
{
   public:
      GlyphData();
      GlyphData(int numGlyphs);

      int numGlyphs();

      void extend(GlyphData *other);

      void extend(GlyphData other);

      void addGlyph(QVector3D position, QVector2D direction, float textureCoordinate);

      QVector<QVector3D> getPositions() const;

      QVector<QVector3D> getDirections() const;

      QVector<float> getTextureCoordinates() const;

   private:

      QVector<QVector3D> positions;
      QVector<QVector3D> directions;
      QVector<float> textureCoordinates;
};

#endif // GLYPHDATA_H

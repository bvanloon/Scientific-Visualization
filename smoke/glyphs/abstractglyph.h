#ifndef ABSTRACTGLYPH_H
#define ABSTRACTGLYPH_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>


class AbstractGlyph
{
   public:
      AbstractGlyph(float texture);
      AbstractGlyph(QVector3D position, QVector3D direction, float scalar);

      float getTexture() const;

      void setTexture(float value);

      QVector<QVector3D> getGlyphPoints() const;

      void setGlyphPoints(const QVector<QVector3D>& value);

   protected:
      QVector<QVector3D> glyphPoints;
      float texture;
};

#endif // ABSTRACTGLYPH_H

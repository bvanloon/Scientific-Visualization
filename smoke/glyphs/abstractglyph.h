#ifndef ABSTRACTGLYPH_H
#define ABSTRACTGLYPH_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>


class AbstractGlyph
{
   public:
      AbstractGlyph(float textureCoordinate);
      AbstractGlyph(QVector3D position, QVector3D direction, float scalar);

      float getTextureCoordinate() const;

      void setTextureCoordinate(float value);

      QVector<QVector3D> getVertices() const;

      void setVertices(const QVector<QVector3D>& value);

   protected:
      QVector<QVector3D> vertices;
      float textureCoordinate;
};

#endif // ABSTRACTGLYPH_H

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

      QVector<QVector3D> getVertices() const;

   protected:
      float textureCoordinate;
      void addVertex(QVector3D vertex, QVector3D normal);

    private:
      QVector<QVector3D> normals;
      QVector<QVector3D> vertices;
};

#endif // ABSTRACTGLYPH_H

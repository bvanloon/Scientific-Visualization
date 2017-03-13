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

      QVector<QVector3D> getNormals() const;

      size_t numVertices();

   protected:
      float textureCoordinate;
      QVector<QVector3D> normals;
      QVector<QVector3D> vertices;

      void addVertex(QVector3D vertex, QVector3D normal);
      void addVertices(QVector<QVector3D> vertices, QVector3D normal);

   private:
};

#endif // ABSTRACTGLYPH_H

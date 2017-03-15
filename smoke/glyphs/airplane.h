#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector3D>
#include "glyphs/abstractglyph.h"
#include "utilities/mesh.h"

class Airplane : public AbstractGlyph
{
   public:
      Airplane(QVector3D position, QVector3D direction, float scalar);

   private:
      class AirplaneBuilder;
};

class Airplane::AirplaneBuilder {
   public:
      AirplaneBuilder(QVector3D position, QVector3D direction);

      QVector<QVector3D> getNormals();

      QVector<QVector3D> getVertices();

   private:
      QVector3D direction;
      QVector3D orthogonalDirection;
      QVector3D position;
      float normalizedMagnitude;

      mesh::TriangleMesh mesh;

      float baseEdgeLength();

      static const float maxSize;
      static const float minSize;

      QVector3D computeNose();
      QVector3D computeLeftWing();
      QVector3D computeRightWing();
      QVector3D computeWing(int direction);
};

#endif // AIRPLANE_H

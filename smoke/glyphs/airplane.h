#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector3D>
#include "glyphs/abstractglyph.h"
#include "utilities/mesh.h"

class Airplane : public AbstractGlyph
{
   public:
      Airplane(QVector3D position, QVector3D direction);

      GPUData toGPUData(float textureCoordinate);

   private:
      class AirplaneBuilder;
};

class Airplane::AirplaneBuilder {
   public:
      AirplaneBuilder(QVector3D position, QVector3D direction, float normalizedMagnitude);

      QVector<QVector3D> getNormals();

      QVector<QVector3D> getVertices();

   private:
      QVector3D direction;
      QVector3D orthogonalDirection;
      QVector3D position;

      float normalizedMagnitude;

      double baseSize;

      mesh::TriangleMesh mesh;

      float baseEdgeLength();

      static const double maxCellRatio;

      QVector3D computeNose();

      QVector3D computeBase();

      QVector3D computeLeftWing();

      QVector3D computeRightWing();

      QVector3D computeWing(int direction);

      void determineSizeRange();
};

#endif // AIRPLANE_H

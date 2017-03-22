#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include "abstractengine.h"
#include "unused.h"
#include "utilities/mesh.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();

      void draw(Simulation *UNUSED(simulation));

   private:
      int updateBuffers();

      void fillIntermediateBuffers();

      void addSeedPoint(QPointF position);

      void addSeedPointBorder(QPointF position);

      void addSeedPointFill(QPointF position);

      void addMesh(mesh::TriangleMesh* mesh, float textureCoordinate);

      void clearIntermediateBuffers();

      int intermediateBufferSize();

      static const int drawMode = GL_TRIANGLES;
      static const double borderScale;
      static const double fillScale;

      QVector<QVector3D> vertices;
      QVector<QVector3D> normals;
      QVector<float> textureCoordinates;
};

#endif // SEEDPOINTENGINE_H

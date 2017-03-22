#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include "abstractengine.h"
#include "unused.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();

      void draw(Simulation *UNUSED(simulation));

   private:
      int updateBuffers();

      void fillIntermediateBuffers();
      void clearIntermediateBuffers();
      int intermediateBufferSize();

      static const int drawMode = GL_TRIANGLES;

      QVector<QVector3D> vertices;
      QVector<QVector3D> normals;
      QVector<float> textureCoordinates;
};

#endif // SEEDPOINTENGINE_H

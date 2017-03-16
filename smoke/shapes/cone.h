#ifndef CONE_H
#define CONE_H

#include "utilities/mesh.h"

class Cone
{
   public:
      Cone();

      mesh::TriangleMesh* toTriangleMesh(int resolution = 5);

   private:

      QVector3D center;
      QVector3D direction;
      float height;

      int computeNumFaces(int resolution);
      int computeNumVertices(int resolution);
      QVector3D computeTop();
      QVector3D computeBottomCenter();
};

#endif // CONE_H

#ifndef CONE_H
#define CONE_H

#include "utilities/mesh.h"

class Cone
{
   public:
      Cone();

      mesh::TriangleMesh *toTriangleMesh(int resolution = 5);

   private:

      QVector3D center;
      QVector3D direction;
      float height;

      class MeshBuilder {
         public:
            MeshBuilder(Cone *cone, int resolution);

            mesh::TriangleMesh *getMesh() const;

         private:
            Cone *cone;
            int resolution;

            mesh::TriangleMesh *mesh;

            mesh::Vertex* top;
            mesh::Vertex* bottomCenter;

            int computeNumFaces();

            int computeNumVertices();

            QVector3D computeTop();

            QVector3D computeBottomCenter();
      };
};

#endif // CONE_H

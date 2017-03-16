#ifndef SHAPES_CONE_H
#define SHAPES_CONE_H

#include "utilities/mesh.h"

namespace shapes {
    class Cone
    {
       public:
          Cone();

          mesh::TriangleMesh *toTriangleMesh(int resolution = 5);

       private:

          QVector3D center;
          QVector3D direction;

          float height;
          float radius;

          class MeshBuilder {
             public:
                MeshBuilder(Cone *cone, int resolution);

                mesh::TriangleMesh *getMesh() const;

             private:
                Cone *cone;
                int resolution;

                QVector3D perpendicularDirection;

                mesh::TriangleMesh *mesh;

                mesh::Vertex *top;
                mesh::Vertex *bottomCenter;

                int computeNumFaces();

                int computeNumVertices();

                QVector3D computeTopPosition();

                QVector3D computeBottomCenterPosition();

                void addFaces();

                void addFacesWithEdge(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB);

                void addBottomFace(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB);

                void addSideFace(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB);
          };
    };
}

#endif // SHAPES_CONE_H

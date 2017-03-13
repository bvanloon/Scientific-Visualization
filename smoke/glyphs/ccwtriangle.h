#ifndef GLYPHTRIANGLE_H
#define GLYPHTRIANGLE_H

#include <QVector>
#include <QVector3D>

class CCWTriangle
{
   public:
      CCWTriangle(QVector3D a, QVector3D b, QVector3D c);
      QVector3D getA();

      QVector3D getB();

      QVector3D getC();

      QVector<QVector3D> getVertices();

      QVector3D computeForwardPointingFaceNormal();

      bool hasCCWwindingOrder();

   protected:
      QVector3D vertexA, vertexB, vertexC;

    private:
      void swapVertices();
};

#endif // GLYPHTRIANGLE_H

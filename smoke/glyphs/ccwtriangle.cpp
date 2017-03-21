#include "ccwtriangle.h"
#include "QDebug"

CCWTriangle::CCWTriangle(QVector3D a, QVector3D b, QVector3D c) :
   vertexA(a), vertexB(b), vertexC(c)
{
   if (!hasCCWwindingOrder()) swapVertices();
}

QVector3D CCWTriangle::getA()
{
   return this->vertexA;
}

QVector3D CCWTriangle::getB()
{
   return this->vertexB;
}

QVector3D CCWTriangle::getC()
{
   return this->vertexC;
}

QVector<QVector3D> CCWTriangle::getVertices()
{
   QVector<QVector3D> vertices;
   vertices.append(vertexA);
   vertices.append(vertexB);
   vertices.append(vertexC);

   return vertices;
}

QVector3D CCWTriangle::computeForwardPointingFaceNormal()
{
   QVector3D ab = vertexB - vertexA;
   QVector3D ac = vertexC - vertexA;

   return QVector3D::crossProduct(ac, ab).normalized();
}

bool CCWTriangle::hasCCWwindingOrder()
{
   QVector3D ab = vertexB - vertexA;
   QVector3D ac = vertexC - vertexA;
   double crossProductZ = ab.x() * ac.y() - ab.y() * ac.x();

   return crossProductZ < 0.0;
}

void CCWTriangle::swapVertices()
{
   QVector3D temp = vertexA;

    vertexA = vertexB;
    vertexB = temp;
}

#include "qtriangle.h"

QTriangle::QTriangle()
{}

QTriangle::QTriangle(QVector3D a, QVector3D b, QVector3D c)
{
   this->pointA = a;
   this->pointB = b;
   this->pointC = c;
}

QVector3D QTriangle::getA()
{
   return this->pointA;
}

QVector3D QTriangle::getB()
{
   return this->pointB;
}

QVector3D QTriangle::getC()
{
   return this->pointC;
}

QVector<QVector3D> QTriangle::getVertices()
{
   QVector<QVector3D> vertices;
   vertices.append(pointA);
   vertices.append(pointB);
   vertices.append(pointC);

   return vertices;
}

void QTriangle::setPointA(const QVector3D& value)
{
   pointA = value;
}

void QTriangle::setPointB(const QVector3D& value)
{
   pointB = value;
}

void QTriangle::setPointC(const QVector3D& value)
{
   pointC = value;
}

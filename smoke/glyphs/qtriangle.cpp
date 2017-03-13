#include "qtriangle.h"
#include "QDebug"

QTriangle::QTriangle()
{}

QTriangle::QTriangle(QVector3D a, QVector3D b, QVector3D c)
{
   this->vertexA = a;
   this->vertexB = b;
   this->vertexC = c;
}

QVector3D QTriangle::getA()
{
   return this->vertexA;
}

QVector3D QTriangle::getB()
{
   return this->vertexB;
}

QVector3D QTriangle::getC()
{
   return this->vertexC;
}

QVector<QVector3D> QTriangle::getAllVertices()
{
   QVector<QVector3D> vertices;
   vertices.append(vertexA);
   vertices.append(vertexB);
   vertices.append(vertexC);

   return vertices;
}

void QTriangle::setVertexA(const QVector3D& value)
{
   vertexA = value;
}

void QTriangle::setVertexB(const QVector3D& value)
{
   vertexB = value;
}

void QTriangle::setVertexC(const QVector3D& value)
{
    vertexC = value;
}

QVector3D QTriangle::computeFaceNormal()
{
    qDebug() << "QTriangle::computeFaceNormal: Not Implemented";
}

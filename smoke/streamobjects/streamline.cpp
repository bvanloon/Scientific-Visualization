#include "streamline.h"

streamobject::Line::Line(QVector3D seedPoint, float textureCoordinate) :
   shapes::PolyLine(seedPoint)
{
   this->textureCoordinates.append(textureCoordinate);
}

streamobject::Line::Line() :
   shapes::PolyLine()
{}

GPUData streamobject::Line::toGPUData() const
{
   GPUData data;

   QVector3D normal = QVector3D(0.0, 0.0, 1.0);

   if (this->numVertices() <= 1) return data;

   for (int current = 0, next = 1; next < this->vertices.length(); current++, next++)
   {
      data.addElement(this->vertices[current], normal, this->textureCoordinates[current]);
      data.addElement(this->vertices[next], normal, this->textureCoordinates[next]);
   }
   return data;
}

int streamobject::Line::numVertices() const
{
    return this->vertices.length();
}

int streamobject::Line::getLength() const
{
    return this->getLength();
}

void streamobject::Line::addVertex(QVector3D vertex, float textureCoordinate)
{
   shapes::PolyLine::addVertex(vertex);
   this->textureCoordinates.append(textureCoordinate);
}

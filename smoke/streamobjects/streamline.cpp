#include "streamline.h"

streamobject::Line::Line(QVector3D seedPoint, float textureCoordinate) :
   shapes::PolyLine(seedPoint)
{
   this->textureCoordinates.append(textureCoordinate);
}

streamobject::Line::Line(QPointF seedPoint, float textureCoordinate) :
   shapes::PolyLine(seedPoint)
{
   this->textureCoordinates.append(textureCoordinate);
}

streamobject::Line::Line():
    shapes::PolyLine()
{}

GPUData streamobject::Line::toGPUData() const
{
   GPUData data;
   int next, current = 0;
   QVector3D normal = QVector3D(0.0, 0.0, 1.0);

   do
   {
      next = current + 1;

      data.addElement(this->vertices[current], normal, this->textureCoordinates[current]);
      data.addElement(this->vertices[next], normal, this->textureCoordinates[next]);

      current = next;
   } while (current + 1 != this->vertices.length());

   return data;
}

void streamobject::Line::addVertex(QVector3D vertex, float textureCoordinate)
{
   shapes::PolyLine::addVertex(vertex);
   this->textureCoordinates.append(textureCoordinate);
}

void streamobject::Line::addVertex(QPointF vertex, float textureCoordinate)
{
   shapes::PolyLine::addVertex(vertex);
   this->textureCoordinates.append(textureCoordinate);
}

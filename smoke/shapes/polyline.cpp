#include "polyline.h"
#include "assert.h"
#include <QDebug>

shapes::PolyLine::PolyLine(QVector3D start) :
   length(0)
{
   this->vertices.append(start);
}

shapes::PolyLine::PolyLine() :
   length(0)
{}

void shapes::PolyLine::addVertex(QVector3D vertex)
{
   updateLength(vertex);
   this->vertices.append(vertex);
}

void shapes::PolyLine::updateLength(QVector3D newVertex)
{
   if (this->vertices.length() < 2) return;

   QVector3D newEdge = newVertex - this->vertices.last();
   assert(newEdge.length() > 0);
   this->length += newEdge.length();
}

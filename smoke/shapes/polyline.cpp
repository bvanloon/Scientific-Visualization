#include "polyline.h"
#include <QDebug>

shapes::PolyLine::PolyLine(QVector3D start)
{
   this->vertices.append(start);
}

shapes::PolyLine::PolyLine(QPointF start)
{
   this->vertices.append(QVector3D(start));
}

shapes::PolyLine::PolyLine()
{}

void shapes::PolyLine::addVertex(QVector3D vertex)
{
   this->vertices.append(vertex);
}

void shapes::PolyLine::addVertex(QPointF vertex)
{
   addVertex(QVector3D(vertex));
}

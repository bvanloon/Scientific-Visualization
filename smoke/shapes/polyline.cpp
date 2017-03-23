#include "polyline.h"
#include <QDebug>

shapes::PolyLine::PolyLine(QVector3D start)
{
   this->vertices.append(start);
}

void shapes::PolyLine::addVertex(QVector3D vertex)
{
   this->vertices.append(vertex);
}

GPUData shapes::PolyLine::toGPUData() const
{
   GPUData data;

   QList<QVector3D>::const_iterator current = this->vertices.begin();
   QList<QVector3D>::const_iterator next;

   QVector3D normal = QVector3D(0.0, 0.0, 1.0);

   do
   {
      next = current + 1;

      data.addElement(*current, normal);
      data.addElement(*next, normal);

      current = next;
   } while (current + 1 != this->vertices.end());

   return data;
}

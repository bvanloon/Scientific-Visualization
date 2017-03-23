#ifndef POLYLINE_H
#define POLYLINE_H

#include <QVector3D>
#include <QList>
#include <QPointF>
#include "utilities/gpudata.h"

namespace shapes {
    class PolyLine
    {
       public:
          PolyLine(QVector3D start);
          PolyLine();

          void addVertex(QVector3D vertex);

          double getLength() const;

       protected:
          QList<QVector3D> vertices;
          double length;

          void updateLength(QVector3D newVertex);
    };
}

#endif // POLYLINE_H

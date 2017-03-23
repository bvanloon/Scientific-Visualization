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
          PolyLine(QPointF start);
          PolyLine();

          void addVertex(QVector3D vertex);

          void addVertex(QPointF vertex);

       protected:
          QList<QVector3D> vertices;
    };
}

#endif // POLYLINE_H

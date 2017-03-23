#ifndef POLYLINE_H
#define POLYLINE_H

#include <QVector3D>
#include <QList>
#include "utilities/gpudata.h"

namespace shapes {
    class PolyLine
    {
       public:
          PolyLine(QVector3D start);

          void addVertex(QVector3D vertex);

          GPUData toGPUData() const;

       private:
          QList<QVector3D> vertices;
    };
}

#endif // POLYLINE_H

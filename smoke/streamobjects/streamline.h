#ifndef STREAMLINE_H
#define STREAMLINE_H

#include <QVector3D>
#include <QPointF>
#include <QList>

#include "shapes/polyline.h"
#include "utilities/gpudata.h"

namespace streamobject {
    class Line : protected shapes::PolyLine
    {
       public:
          Line(QVector3D seedPoint, float textureCoordinate);
          Line(QPointF seedPoint, float textureCoordinate);

          void addVertex(QVector3D vertex, float textureCoordinate);
          void addVertex(QPointF vertex, float textureCoordinate);

          GPUData toGPUData() const;

       private:
          QList<float> textureCoordinates;
    };
}

#endif // STREAMLINE_H

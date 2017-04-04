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
          Line();

          void addVertex(QVector3D vertex, float textureCoordinate);

          bool hasNoVertices();

          GPUData toGPUData() const;

          int numVertices() const;

          int getLength() const;

          static const int drawMode = GL_LINES;

       private:
          QList<float> textureCoordinates;
          bool isEdgeAllowed(QVector3D vertex);

          static const double minimalEdgeSize;
    };
}

#endif // STREAMLINE_H

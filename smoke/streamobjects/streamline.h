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
          Line(QVector3D seedPoint, float textureCoordinate, float alpha = 1.0);
          Line(QPointF seedPoint, float textureCoordinate, float alpha = 1.0);
          Line();

          void addVertex(QVector3D vertex, float textureCoordinate, float alpha = 1.0);

          bool hasNoVertices();

          GPUData toGPUData() const;

          int numVertices() const;

          int getLength() const;

          static const int drawMode = GL_LINES;

       private:
          QList<float> textureCoordinates;
          QList<float> alphaValues;
          bool isEdgeAllowed(QVector3D vertex);

          static const double minimalEdgeSize;
    };
}

#endif // STREAMLINE_H

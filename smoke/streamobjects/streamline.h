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

          typedef QList<QVector3D>::ConstIterator ConstIterator;
          typedef QList<QVector3D>::Iterator Iterator;

          void addVertex(QVector3D vertex, float textureCoordinate, float alpha = 1.0);

          bool hasNoVertices();

          GPUData GPUDataEdges() const;

          GPUData GPUDataEdges(float textureCoordinate) const;

          GPUData GPUDataVertices(float textureCoordinate) const;

          int numVertices() const;

          int getLength() const;

          QVector3D vertexAt(int i) const;

       private:
          QList<float> textureCoordinates;
          QList<float> alphaValues;
          bool isEdgeAllowed(QVector3D vertex);

          static const double minimalEdgeSize;
    };
}

#endif // STREAMLINE_H

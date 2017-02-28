#ifndef ABSTRACTGRID_H
#define ABSTRACTGRID_H

#include <QVector>
#include <QVector3D>
#include "grid/vertex.h"

class Grid
{
public:
    Grid(int numberOfVertices);

    QVector<QVector3D> const& getVertexPositions() const;
    QVector<Vertex> const& getVertices() const;
    int const& numVertices() const;

protected:
    QVector<Vertex> vertices;
    QVector<QVector3D> vertexPositions;
};

#endif // ABSTRACTGRID_H

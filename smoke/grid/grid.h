#ifndef ABSTRACTGRID_H
#define ABSTRACTGRID_H

#include <QVector>
#include <QVector3D>
#include "grid/vertex.h"
#include "grid/cell.h"

class Grid
{
public:
    Grid(int numberOfVertices, bool padding = true);
    ~Grid();

    QVector<QVector3D> const& getVertexPositions() const;
    QVector<Vertex*> const& getVertices() const;
    int numVertices() const;

protected:
    QVector<Vertex*> vertices;
    QVector<QVector3D> vertexPositions;
    QVector<Cell* > cells;
    bool padding;
};

#endif // ABSTRACTGRID_H

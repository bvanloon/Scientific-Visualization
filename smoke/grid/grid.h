#ifndef ABSTRACTGRID_H
#define ABSTRACTGRID_H

#include <QVector>
#include <QVector3D>
#include "grid/vertex.h"
#include "grid/cell.h"

class Grid
{
public:
    Grid(int numberOfVertices, bool hasPadding = true);
    ~Grid();

    QVector<QVector3D> const& getVertexPositions() const;
    QVector<Vertex*> const& getVertices() const;
    QVector<Cell*> const& getCells() const;
    int numVertices() const;

protected:
    QVector<Vertex*> vertices;
    QVector<QVector3D> vertexPositions;
    QVector<Cell* > cells;
    bool hasPadding;

};

#endif // ABSTRACTGRID_H

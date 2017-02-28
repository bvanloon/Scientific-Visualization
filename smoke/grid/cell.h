#ifndef CELL_H
#define CELL_H

#include "grid/vertex.h"
#include <QVector>
#include <QVector3D>

class Cell
{
public:
    Cell();
    virtual ~Cell();

    virtual QVector<QVector3D> triangulate() = 0;
};

class StructuredCell : public Cell
{
public:
    StructuredCell(Vertex* upperLeft, Vertex* upperRight, Vertex* lowerLeft, Vertex* lowerRight);

    friend QDebug operator<<(QDebug stream, const StructuredCell &cell);
    friend QDebug operator<<(QDebug stream, StructuredCell *cell);

    virtual QVector<QVector3D> triangulate();

private:
    Vertex* upperLeft;
    Vertex* upperRight;
    Vertex* lowerLeft;
    Vertex* lowerRight;
};

#endif // CELL_H

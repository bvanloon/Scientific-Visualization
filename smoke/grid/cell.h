#ifndef CELL_H
#define CELL_H

#include "grid/vertex.h"
#include <QVector>
#include <QVector3D>
#include <QSizeF>
#include <grid/triangulation.h>

class Cell
{
public:
    Cell();
    virtual ~Cell();

    virtual Triangulation triangulate() = 0;
};

class StructuredCell : public Cell
{
public:
    StructuredCell(Vertex* upperLeft, Vertex* upperRight, Vertex* lowerLeft, Vertex* lowerRight);

    friend QDebug operator<<(QDebug stream, const StructuredCell &cell);
    friend QDebug operator<<(QDebug stream, StructuredCell *cell);

    virtual Triangulation triangulate();

    QSizeF getSize() const;

private:
    Vertex* upperLeft;
    Vertex* upperRight;
    Vertex* lowerLeft;
    Vertex* lowerRight;

    Triangulation lowerLeftTriangle();
    Triangulation upperRightTriangle();
};

#endif // CELL_H

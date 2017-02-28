#ifndef CELL_H
#define CELL_H

#include "grid/vertex.h"

class Cell
{
public:
    Cell();
    ~Cell();
};

class StructuredCell : public Cell
{
public:
    StructuredCell(Vertex* upperLeft, Vertex* upperRight, Vertex* lowerLeft, Vertex* lowerRight);
    ~StructuredCell();

    friend QDebug operator<<(QDebug stream, const StructuredCell &cell);
    friend QDebug operator<<(QDebug stream, StructuredCell *cell);

private:
    Vertex* upperLeft;
    Vertex* upperRight;
    Vertex* lowerLeft;
    Vertex* lowerRight;
};

#endif // CELL_H

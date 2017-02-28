#include "cell.h"

Cell::Cell()
{}

Cell::~Cell()
{}


StructuredCell::StructuredCell(Vertex *upperLeft, Vertex *upperRight, Vertex *lowerLeft, Vertex *lowerRight):
    Cell(),
    upperLeft(upperLeft),
    upperRight(upperRight),
    lowerLeft(lowerLeft),
    lowerRight(lowerRight)
{}

QDebug operator<<(QDebug stream, const StructuredCell &cell)
{
    stream << "StructuredCell ["
           << " upperLeft: "    << *cell.upperLeft->getPosition()
           << " upperRight: "    << *cell.upperRight->getPosition()
           << " lowerLeft: "    << *cell.lowerLeft->getPosition()
           << " lowerRight: "    << *cell.lowerRight->getPosition()
           << "]";
    return stream;
}

QDebug operator<<(QDebug stream, StructuredCell *cell)
{
    stream << *cell;
    return stream;
}

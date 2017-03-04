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

Triangulation StructuredCell::triangulate()
{
    Triangulation triangulation(6);
    triangulation.extend(lowerLeftTriangle());
    triangulation.extend(upperRightTriangle());
    return triangulation;
}

QSizeF StructuredCell::getSize() const
{
    float width = upperRight->getPosition()->x() - upperLeft->getPosition()->x();
    float height = lowerLeft->getPosition()->y() - upperLeft->getPosition()->y();
    return QSizeF(width, height);
}

Triangulation StructuredCell::lowerLeftTriangle()
{
    Triangulation triangulation(3);
    triangulation.addVertex(upperLeft);
    triangulation.addVertex(lowerLeft);
    triangulation.addVertex(lowerRight);
    return triangulation;
}

Triangulation StructuredCell::upperRightTriangle()
{
    Triangulation triangulation(3);
    triangulation.addVertex(upperLeft);
    triangulation.addVertex(lowerRight);
    triangulation.addVertex(upperRight);
    return triangulation;
}

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

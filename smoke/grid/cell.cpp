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

//QVector<QVector3D> StructuredCell::triangulate()
//{
//    QVector<QVector3D> triangulation;
//    triangulation.append(*upperLeft->getPosition());
//    triangulation.append(*lowerLeft->getPosition());
//    triangulation.append(*lowerRight->getPosition());

//    triangulation.append(*upperLeft->getPosition());
//    triangulation.append(*lowerRight->getPosition());
//    triangulation.append(*upperRight->getPosition());
//    return triangulation;
//}

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

#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <QVector>
#include <QVector3D>
#include <grid/vertex.h>

class Triangulation
{
public:
    static Triangulation* fromCell(Cell* cell);

    QVector<QVector3D> getVertexPositions() const;

    QVector<Vertex *> getVertices() const;

private:
    Triangulation(int numVertices);

    QVector<QVector3D> vertexPositions;
    QVector<Vertex*> vertices;
};

#endif // TRIANGULATION_H

#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension, QSizeF size, bool padding):
    Grid(dimension * dimension),
    dimension(dimension)
{
    cellSize = size / ((float) (dimension + 1));
    this->create();
}

const QVector<QVector3D> &UniformGrid::getVertexPositions() const
{
    return this->vertexPositions;
}

void UniformGrid::create()
{
    QVector3D position;
    int idx;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            idx = to1Dindex(i, j);
            position = QVector3D(
                        cellSize.width() + (double)i * cellSize.width(),
                        cellSize.height() + (double)j * cellSize.height(),
                        0.0f);
            this->vertexPositions.replace(idx, position);
            this->vertices.replace(idx, Vertex(&this->vertexPositions.at(idx)));
        }
    }
    qDebug() << this->vertexPositions;
}

int UniformGrid::to1Dindex(int i, int j)
{
    return (j * this->dimension) + i;
}

#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension, QSizeF size):
    Grid(dimension * dimension),
    dimension(dimension)
{
    cellSize = size / ((float) (dimension + 1));
}

const QVector<QVector3D> &UniformGrid::getVertexPositions() const
{
    return this->vertexPositions;
}

UniformGrid *UniformGrid::createSimulationGrid(int dimension, QSizeF size)
{
    UniformGrid* grid = new UniformGrid(dimension, size);
    QVector3D position;
    int idx;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            idx = grid->to1Dindex(i, j);
            position = QVector3D(
                        grid->cellSize.width() + (double)i * grid->cellSize.width(),
                        grid->cellSize.height() + (double)j * grid->cellSize.height(),
                        0.0f);
            grid->vertexPositions.replace(idx, position);
            grid->vertices.replace(idx, Vertex(&grid->vertexPositions.at(idx)));
        }
    }
    return grid;
}

int UniformGrid::to1Dindex(int i, int j)
{
    return (j * this->dimension) + i;
}

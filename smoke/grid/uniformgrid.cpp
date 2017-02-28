#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension, QSizeF areaSize):
    Grid(dimension * dimension),
    dimension(dimension),
    cellSize(computeCellSize(areaSize))
{}

const QVector<QVector3D> &UniformGrid::getVertexPositions() const
{
    return this->vertexPositions;
}

const QVector<QVector3D> &UniformGrid::getTriangulation() const
{
    QVector<QVector3D> triangulation;
    Vertex* vertex;
    for(int i = 0; i < dimension - 1; i++){
        for(int j = 0; j < dimension - 1; j++){
            vertex = getVertexAt(i, j);
        }
    }
    return triangulation;
}

void UniformGrid::recomputeVertexPositions()
{
    QVector3D position;
    Vertex* vertex;
    int idx;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            idx = to1Dindex(i, j);
            vertexPositions.replace(idx, computeVertexPosition(i, j));
        }
    }
}

QSizeF UniformGrid::computeCellSize(QSizeF area)
{
    return area / ((float) (dimension + 1));
}

UniformGrid *UniformGrid::createSimulationGrid(int dimension, QSizeF size, SimulationRealization* simulation)
{
    UniformGrid* grid = new UniformGrid(dimension, size);
    QVector3D position;
    Vertex* vertex;
    int idx;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            idx = grid->to1Dindex(i, j);
            position = grid->computeVertexPosition(i, j);
            grid->vertexPositions.replace(idx, position);
            vertex = new SimulationVertex(&grid->vertexPositions.at(idx),
                                          &simulation->vx[idx], &simulation->vy[idx]);
            grid->vertices.replace(idx, vertex);
        }
    }
    return grid;
}

int UniformGrid::to1Dindex(int i, int j) const
{
    return (j * this->dimension) + i;
}

void UniformGrid::changeGridArea(QSizeF newArea)
{
    cellSize = computeCellSize(newArea);
    recomputeVertexPositions();
}

QVector3D UniformGrid::computeVertexPosition(int i, int j)
{
    return QVector3D(cellSize.width() + (double)i * cellSize.width(),
              cellSize.height() + (double)j * cellSize.height(),
              0.0f);
}

Vertex *UniformGrid::getVertexAt(int idx) const
{
    return vertices.at(idx);
}

Vertex *UniformGrid::getVertexAt(int i, int j) const
{
    int idx = to1Dindex(i, j);
    return getVertexAt(idx);
}

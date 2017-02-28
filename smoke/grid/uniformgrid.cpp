#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "grid/cell.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, bool padding):
    Grid(dimension * dimension, padding),
    dimension(dimension),
    cellSize(computeCellSize(areaSize))
{}

const QVector<QVector3D> &UniformGrid::getVertexPositions() const
{
    return this->vertexPositions;
}

QVector<QVector3D> UniformGrid::getTriangulation() const
{
    QVector<QVector3D> triangulation;
    Vertex* vertex, *rightBelow, *right, *below;
    for(int rowIdx = 0; rowIdx < dimension - 1; rowIdx++){
        for(int colIdx = 0; colIdx < dimension - 1; colIdx++){
            vertex = getVertexAt(colIdx, rowIdx);
            right = getVertexAt(colIdx + 1, rowIdx);
            below = getVertexAt(colIdx, rowIdx + 1);
            rightBelow = getVertexAt(colIdx + 1, rowIdx + 1);

            triangulation.append(*vertex->getPosition());
            triangulation.append(*below->getPosition());
            triangulation.append(*rightBelow->getPosition());

            triangulation.append(*vertex->getPosition());
            triangulation.append(*rightBelow->getPosition());
            triangulation.append(*right->getPosition());
        }
    }
    return triangulation;
}

void UniformGrid::recomputeVertexPositions()
{
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
    return area / ((float) (dimension + (padding ? 1.0 : -1.0)));
}

UniformGrid *UniformGrid::createSimulationGrid(int dimension, QSizeF size, SimulationRealization* simulation)
{
    UniformGrid* grid = new UniformGrid(dimension, size, true);
    createVertices(grid, simulation);
    createCells(grid);
    return grid;
}

void UniformGrid::createVertices(UniformGrid *grid, SimulationRealization *simulation)
{
    QVector3D position;
    Vertex* vertex;
    int idx;
    for (int i = 0; i < grid->dimension; i++){
        for (int j = 0; j < grid->dimension; j++)
        {
            idx = grid->to1Dindex(i, j);
            position = grid->computeVertexPosition(i, j);
            grid->vertexPositions.replace(idx, position);
            vertex = new SimulationVertex(&grid->vertexPositions.at(idx),
                                          &simulation->vx[idx], &simulation->vy[idx]);
            grid->vertices.replace(idx, vertex);
        }
    }
}

void UniformGrid::createCells(UniformGrid *grid)
{
    Cell* cell;
    Vertex* vertex, *rightBelow, *right, *below;
    for(int rowIdx = 0; rowIdx < grid->dimension - 1; rowIdx++){
        for(int colIdx = 0; colIdx < grid->dimension - 1; colIdx++){
            vertex = grid->getVertexAt(colIdx, rowIdx);
            right = grid->getVertexAt(colIdx + 1, rowIdx);
            below = grid->getVertexAt(colIdx, rowIdx + 1);
            rightBelow = grid->getVertexAt(colIdx + 1, rowIdx + 1);

            cell = new StructuredCell(vertex, right, below, rightBelow);
            grid->cells.append(cell);
        }
    }
}

int UniformGrid::to1Dindex(int coldIdx, int rowIdx) const
{
    return (rowIdx * this->dimension) + coldIdx;
}

void UniformGrid::changeGridArea(QSizeF newArea)
{
    cellSize = computeCellSize(newArea);
    recomputeVertexPositions();
}

QVector3D UniformGrid::computeVertexPosition(int i, int j)
{
    return QVector3D(padding * cellSize.width() + (double)i * cellSize.width(),
                     padding * cellSize.height() + (double)j * cellSize.height(),
                     0.0f);
}

Vertex *UniformGrid::getVertexAt(int idx) const
{
    return vertices.at(idx);
}

Vertex *UniformGrid::getVertexAt(int coldIdx, int rowIdx) const
{
    int idx = to1Dindex(coldIdx, rowIdx);
    return getVertexAt(idx);
}

#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "grid/cell.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, bool hasPadding):
    Grid(dimension * dimension, hasPadding),
    dimension(dimension),
    cellSize(computeCellSize(areaSize)),
    padding(0, 0)
{
    if(hasPadding) padding = cellSize;
}

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, QSizeF padding):
    Grid(dimension * dimension, true),
    dimension(dimension),
    cellSize(computeCellSize(areaSize, padding)),
    padding(padding)
{}

const QVector<QVector3D> &UniformGrid::getVertexPositions() const
{
    return this->vertexPositions;
}

QVector<QVector3D> UniformGrid::getTriangulation() const
{
    QVector<QVector3D> triangulation;
    QVector<Cell*>::const_iterator currentCell = cells.begin();
    while(currentCell != cells.end()){
        triangulation.append((*currentCell++)->triangulate());
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
    return area / ((float) (dimension + (hasPadding ? 1.0 : -1.0)));
}

QSizeF UniformGrid::computeCellSize(QSizeF area, QSizeF padding)
{
    QSizeF usedArea = (area - padding * 2);
    QSizeF cellSize = usedArea / ((float) (dimension - 1));
    return cellSize;
}

UniformGrid *UniformGrid::createSimulationGrid(int dimension, QSizeF size, SimulationRealization* simulation)
{
    UniformGrid* grid = new UniformGrid(dimension, size, true);
    createVertices(grid, simulation);
    createCells(grid);
    return grid;
}

UniformGrid *UniformGrid::createVisualizationGrid(int dimension, QSizeF size, UniformGrid *simulationGrid)
{
    UniformGrid* grid = new UniformGrid(dimension, size, simulationGrid->padding);
    createVertices(grid, simulationGrid);
    createCells(grid);
    return grid;
}

Cell *UniformGrid::findCellContaining(QVector3D position)
{
    qDebug() << "UniformGrid::findCellContaining(QVector3D position) IMPLEMENT";
    return cells.at(0);

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
            grid->vertexMap.insert(QPair<int, int>(i, j), vertex);
        }
    }
}

void UniformGrid::createVertices(UniformGrid *visualizationGrid, UniformGrid *simulationGrid)
{
    QVector3D position;
    Vertex* vertex;
    Cell* cell;
    int idx;
    for (int i = 0; i < visualizationGrid->dimension; i++){
        for (int j = 0; j < visualizationGrid->dimension; j++)
        {
            idx = visualizationGrid->to1Dindex(i, j);
            position = visualizationGrid->computeVertexPosition(i, j);
            visualizationGrid->vertexPositions.replace(idx, position);
            cell = simulationGrid->findCellContaining(position);
            vertex = new VisualizationVertex(&visualizationGrid->vertexPositions.at(idx), cell);
            visualizationGrid->vertices.replace(idx, vertex);
            visualizationGrid->vertexMap.insert(QPair<int, int>(i, j), vertex);
        }
    }
}

void UniformGrid::createCells(UniformGrid *grid)
{
    Cell* cell;
    Vertex* leftUpper, *rightLower, *rightUpper, *leftLower;
    for(int x = 0; x < grid->dimension - 1; x++){
        for(int y = 0; y < grid->dimension - 1; y++){
            leftUpper = grid->getVertexAt(x, y);
            rightUpper = grid->getVertexAt(x + 1, y);
            leftLower = grid->getVertexAt(x, y + 1);
            rightLower = grid->getVertexAt(x + 1, y + 1);

            cell = new StructuredCell(leftUpper, rightUpper, leftLower, rightLower);
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
    return QVector3D(padding.width() + (double)i * cellSize.width(),
                     padding.height() + (double)j * cellSize.height(),
                     0.0f);
}

const QSizeF &UniformGrid::getPadding() const
{
    return padding;
}

Vertex *UniformGrid::getVertexAt(int x, int y) const
{
    return vertexMap.find(QPair<int, int>(x, y)).value();
}

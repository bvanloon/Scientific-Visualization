#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"

class UniformGrid : public Grid
{
public:
    QVector<QVector3D> const& getVertexPositions() const;
    QVector<QVector3D> getTriangulation() const;

    void changeGridArea(QSizeF newArea);

    static UniformGrid *createSimulationGrid(int dimension, QSizeF size, SimulationRealization *simulation);
    static UniformGrid *createVisualizationGrid(int dimension, QSizeF size, UniformGrid* simulationGrid);

private:
    int dimension;
    QSizeF cellSize;
    QSizeF padding;

    Cell* findCellContaining(QVector3D position);

    UniformGrid(int dimension, QSizeF areaSize, bool hasPadding);
    UniformGrid(int dimension, QSizeF areaSize, QSizeF padding);

    void recomputeVertexPositions();
    QSizeF computeCellSize(QSizeF area);
    QSizeF computeCellSize(QSizeF area, QSizeF padding);

    int to1Dindex(int x, int y) const;

    QVector3D computeVertexPosition(int i, int j);

    QSizeF const& getPadding() const;

    Vertex* getVertexAt(int x, int y) const;

    static void createVertices(UniformGrid* grid, SimulationRealization *simulation);
    static void createVertices(UniformGrid* visualizationGrid, UniformGrid* simulationGrid);
    static void createCells(UniformGrid* grid);

};

#endif // UNIFORMGRID_H

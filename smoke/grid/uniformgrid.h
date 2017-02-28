#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"

class UniformGrid : public Grid
{
public:
    UniformGrid(int dimension, QSizeF size);

    QVector<QVector3D> const& getVertexPositions() const;

    static UniformGrid *createSimulationGrid(int dimension, QSizeF size, SimulationRealization *simulation);

private:
    int dimension;
    QSizeF cellSize;

    int to1Dindex(int i, int j);
};

#endif // UNIFORMGRID_H

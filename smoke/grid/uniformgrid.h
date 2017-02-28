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

private:
    int dimension;
    QSizeF cellSize;

    UniformGrid(int dimension, QSizeF areaSize, bool padding);

    void recomputeVertexPositions();
    QSizeF computeCellSize(QSizeF area);

    int to1Dindex(int coldIdx, int rowIdx) const;

    QVector3D computeVertexPosition(int i, int j);

    Vertex* getVertexAt(int idx) const;
    Vertex* getVertexAt(int coldIdx, int rowIdx) const;

};

#endif // UNIFORMGRID_H

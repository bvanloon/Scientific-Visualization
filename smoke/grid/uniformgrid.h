#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>

class UniformGrid : public Grid
{
public:
    UniformGrid(int dimension, QSizeF size, bool padding = true);

    QVector<QVector3D> const& getVertexPositions() const;

private:
    int dimension;
    QSizeF cellSize;

    void create();

    int to1Dindex(int i, int j);
};

#endif // UNIFORMGRID_H

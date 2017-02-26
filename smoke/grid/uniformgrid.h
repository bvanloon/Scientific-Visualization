#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QRectF>

class UniformGrid : public Grid
{
public:
    UniformGrid(int dimension);

private:
    int dimension;

    void create();

    int to1Dindex(int i, int j);
};

#endif // UNIFORMGRID_H

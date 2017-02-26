#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"

UniformGrid::UniformGrid(int dimension):
    dimension(dimension),
    Grid(dimension * dimension)
{
    this->create();
}

void UniformGrid::create()
{
}

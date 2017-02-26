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
    QVector3D position;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            position = QVector3D(
                        Settings::simulation().cellSize.width() + (double)i * Settings::simulation().cellSize.width(),
                        Settings::simulation().cellSize.height() + (double)j * Settings::simulation().cellSize.height(),
                        0.0f);
        }
    }
}

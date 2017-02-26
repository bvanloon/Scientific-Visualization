#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include <QDebug>

UniformGrid::UniformGrid(int dimension):
    Grid(dimension * dimension),
    dimension(dimension)
{
    this->create();
}

void UniformGrid::create()
{
    QVector3D position;
    Vertex vertex;
    int idx;
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++)
        {
            idx = to1Dindex(i, j);
            qDebug() << "(" << i <<", " << j << ") = " << idx;
            position = QVector3D(
                        Settings::simulation().cellSize.width() + (double)i * Settings::simulation().cellSize.width(),
                        Settings::simulation().cellSize.height() + (double)j * Settings::simulation().cellSize.height(),
                        0.0f);
            this->vertexPositions.replace(idx, position);
            this->vertices.replace(idx, Vertex(&this->vertexPositions.at(idx)));
        }
    }
}

int UniformGrid::to1Dindex(int i, int j)
{
    return (j * this->dimension) + i;
}

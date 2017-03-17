#include "jittergrid.h"
#include "qdebug.h"
JitterGrid::JitterGrid(int dimension, QSizeF areaSize, QSizeF padding) :
   UniformGrid(dimension, areaSize, padding)
{}



UniformGrid *JitterGrid::createVisualizationGrid(int dimension,
                                                 QSizeF size,
                                                 UniformGrid *simulationGrid)
{
   JitterGrid *grid = new JitterGrid(dimension, size, simulationGrid->getPadding());

   createVertices(grid, simulationGrid);
   createCells(grid);
   return dynamic_cast<UniformGrid *>(grid);
}

QVector3D JitterGrid::computeVertexPosition(int i, int j)
{
   return QVector3D(padding.width() + (double)i * cellSize.width(),
                   padding.height() + (double)j * cellSize.height(),
                   0.0f);
}

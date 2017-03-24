#include "jittergrid.h"
#include "qdebug.h"
#include <limits>
JitterGrid::JitterGrid(int dimension, QSizeF areaSize, QSizeF padding) :
   UniformGrid(dimension, areaSize, padding)
{
   re.seed(42);
}

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
   float x = padding.width() + (float)i * cellSize.width();
   float y = padding.height() + (float)j * cellSize.height();

   std::uniform_real_distribution<float> xRange(-cellSize.width() * jitterFactor, cellSize.width() * jitterFactor);
   std::uniform_real_distribution<float> yRange(-cellSize.height() * jitterFactor, cellSize.height() * jitterFactor);

   float xOffset = xRange(re);
   float yOffset = yRange(re);

   QVector3D position = QVector3D(x + xOffset, y + yOffset, 0.0f);

   return boundToGrid(position);
}

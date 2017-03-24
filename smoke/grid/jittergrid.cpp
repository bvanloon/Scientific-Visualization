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

   x += xOffset;
   y += yOffset;

   if (x < padding.width()) x = padding.width() + 10.0 * std::numeric_limits<float>::epsilon();
   if (x > padding.width() + cellSize.width() * (dimension - 1)) x = padding.width() + cellSize.width() * (dimension - 1) - 10.0 * std::numeric_limits<float>::epsilon();

   if (y < padding.height()) y = padding.height() + 10.0 * std::numeric_limits<float>::epsilon();
   if (y > padding.height() + cellSize.height() * (dimension - 1)) y = padding.height() + cellSize.height() * (dimension - 1) - 10.0 * std::numeric_limits<float>::epsilon();



   return QVector3D(x, y, 0.0f);
}

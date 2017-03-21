#include "jittergrid.h"
#include "qdebug.h"
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
   double x = padding.width() + (double)i * cellSize.width();
   double y = padding.height() + (double)j * cellSize.height();

   std::uniform_real_distribution<double> xRange(-cellSize.width() * jitterFactor, cellSize.width() * jitterFactor);
   std::uniform_real_distribution<double> yRange(-cellSize.height() * jitterFactor, cellSize.height() * jitterFactor);

   double xOffset = xRange(re);
   double yOffset = yRange(re);

   x += xOffset;
   y += yOffset;


   if (x < padding.width()) x = padding.width();
   if (x > padding.width() + cellSize.width() * (dimension - 1)) x = padding.width() + cellSize.width() * (dimension - 1);

   if (y < padding.height()) y = padding.height();
   if (y > padding.height() + cellSize.height() * (dimension - 1)) y = padding.height() + cellSize.height() * (dimension - 1);


   return QVector3D(x, y, 0.0f);
}

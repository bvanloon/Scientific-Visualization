#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "grid/cell.h"
#include <QDebug>
#include <assert.h>
#include <QtMath>

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, bool hasPadding) :
   Grid(dimension * dimension, hasPadding),
   dimension(dimension),
   cellSize(computeCellSize(areaSize)),
   padding(0, 0)
{
   if (hasPadding) padding = cellSize;
   this->coveredArea = computeCoveredArea(areaSize, this->padding);
}

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, QSizeF padding) :
   Grid(dimension * dimension, true),
   dimension(dimension),
   cellSize(computeCellSize(areaSize, padding)),
   padding(padding)
{
   this->coveredArea = computeCoveredArea(areaSize, this->padding);
}

const QVector<QVector3D>& UniformGrid::getVertexPositions() const
{
   return this->vertexPositions;
}

Triangulation UniformGrid::getTriangulation() const
{
   Triangulation triangulation;

   QVector<Cell *>::const_iterator currentCell = cells.begin();

   while (currentCell != cells.end())
   {
      triangulation.extend((*currentCell++)->triangulate());
   }
   return triangulation;
}

void UniformGrid::recomputeVertexPositions()
{
   int idx;

   for (int i = 0; i < dimension; i++)
   {
      for (int j = 0; j < dimension; j++)
      {
         idx = to1Dindex(i, j);
         vertexPositions.replace(idx, computeVertexPosition(i, j));
      }
   }
}

QSizeF UniformGrid::computeCellSize(QSizeF area)
{
   return area / ((float)(dimension + (hasPadding ? 1.0 : -1.0)));
}

QSizeF UniformGrid::computeCellSize(QSizeF area, QSizeF padding)
{
   QSizeF usedArea = (area - padding * 2);
   QSizeF cellSize = usedArea / ((float)(dimension - 1));

   return cellSize;
}

QRectF UniformGrid::computeCoveredArea(QSizeF areaSize, QSizeF padding)
{
   QPointF upperLeftCorner = QPointF(padding.width(), padding.height());

   return QRectF(upperLeftCorner, areaSize);
}

UniformGrid *UniformGrid::createSimulationGrid(int dimension,
                                               QSizeF size,
                                               SimulationRealization *simulation)
{
   UniformGrid *grid = new UniformGrid(dimension, size, true);

   createVertices(grid, simulation);
   createCells(grid);
   return grid;
}

UniformGrid *UniformGrid::createVisualizationGrid(int dimension,
                                                  QSizeF size,
                                                  UniformGrid *simulationGrid)
{
   UniformGrid *grid = new UniformGrid(dimension, size, simulationGrid->padding);

   createVertices(grid, simulationGrid);
   createCells(grid);
   return grid;
}

QSizeF UniformGrid::getCellSize() const
{
   return cellSize;
}

int UniformGrid::getDimension() const
{
   return dimension;
}

streamobject::Line UniformGrid::computeStreamLine(QVector3D seedPoint,
                                                  Vertex::scalarGetter textureCoordinateGetter,
                                                  Vertex::vectorGetter vectorGetter)
{
   return StreamLineBuilder(this, seedPoint,
                             vectorGetter, textureCoordinateGetter).getStreamLine();
}

Cell *UniformGrid::findCellContaining(QVector3D position)
{
   QPair<int, int> coordinates = findUpperLeftOfContainingCell(position);
   StructuredGridVertex *upperLeftVertex = dynamic_cast<StructuredGridVertex *>(vertexMap.find(coordinates).value());
   Cell *containingCell = upperLeftVertex->getLowerRightCell();

   assert(dynamic_cast<StructuredCell *>(containingCell)->isInCell(position));

   return containingCell;
}

QPair<int,
      int> UniformGrid::findUpperLeftOfContainingCell(QVector3D position)
{
   //Fabs accounts for cases where (x - x) > 0.
   int x = qFloor(qFabs((position.x() - padding.width()) / cellSize.width()));
   int y = qFloor(qFabs((position.y() - padding.height()) / cellSize.height()));

   // Account for the borders
   if (y == (dimension - 1)) y--;
   if (x == (dimension - 1)) x--;
   return QPair<int, int>(x, y);
}

void UniformGrid::createVertices(UniformGrid *grid,
                                 SimulationRealization *simulation)
{
   QVector3D position;
   Vertex *vertex;
   int idx;

   for (int y = 0; y < grid->dimension; y++)
   {
      for (int x = 0; x < grid->dimension; x++)
      {
         idx = grid->to1Dindex(x, y);

         position = grid->computeVertexPosition(x, y);
         grid->vertexPositions.replace(idx, position);
         vertex = new SimulationVertex(&grid->vertexPositions.at(idx),
                                    &simulation->vx[idx], &simulation->vy[idx],
                                    &simulation->fx[idx], &simulation->fy[idx],
                                    &simulation->rho[idx]);
         grid->vertices.replace(idx, vertex);
         grid->vertexMap.insert(QPair<int, int>(x, y), vertex);
      }
   }
}

void UniformGrid::createVertices(UniformGrid *visualizationGrid,
                                 UniformGrid *simulationGrid)
{
   QVector3D position;
   Vertex *vertex;
   Cell *cell;
   int idx;

   for (int i = 0; i < visualizationGrid->dimension; i++)
   {
      for (int j = 0; j < visualizationGrid->dimension; j++)
      {
         idx = visualizationGrid->to1Dindex(i, j);
         position = visualizationGrid->computeVertexPosition(i, j);
         visualizationGrid->vertexPositions.replace(idx, position);
         cell = simulationGrid->findCellContaining(position);
         vertex = new VisualizationVertex(&visualizationGrid->vertexPositions.at(
                                         idx), cell);
         visualizationGrid->vertices.replace(idx, vertex);
         visualizationGrid->vertexMap.insert(QPair<int, int>(i, j), vertex);
      }
   }
}

void UniformGrid::createCells(UniformGrid *grid)
{
   Vertex *leftUpper, *rightLower, *rightUpper, *leftLower;

   for (int x = 0; x < grid->dimension - 1; x++)
   {
      for (int y = 0; y < grid->dimension - 1; y++)
      {
         leftUpper = grid->getVertexAt(x, y);
         rightUpper = grid->getVertexAt(x + 1, y);
         leftLower = grid->getVertexAt(x, y + 1);
         rightLower = grid->getVertexAt(x + 1, y + 1);

         grid->cells.append(new StructuredCell(leftUpper, rightUpper, leftLower,
                                            rightLower));

         dynamic_cast<StructuredGridVertex *>(leftUpper)->setLowerRightCell(
        grid->cells.last());
      }
   }
}

int UniformGrid::to1Dindex(int x, int y) const
{
   return x + (y * this->dimension);
}

void UniformGrid::changeGridArea(QSizeF newArea)
{
   cellSize = computeCellSize(newArea);
   if (hasPadding) padding = cellSize;
   recomputeVertexPositions();
   this->coveredArea = computeCoveredArea(newArea, this->padding);
}

void UniformGrid::changeGridArea(QSizeF newArea, QSizeF padding)
{
   if (hasPadding) this->padding = padding;
   cellSize = computeCellSize(newArea, padding);
   recomputeVertexPositions();
   this->coveredArea = computeCoveredArea(newArea, this->padding);
}

QVector3D UniformGrid::computeVertexPosition(int i, int j)
{
   return QVector3D(padding.width() + (double)i * cellSize.width(),
                   padding.height() + (double)j * cellSize.height(),
                   0.0f);
}

const QSizeF& UniformGrid::getPadding() const
{
   return padding;
}

Vertex *UniformGrid::getVertexAt(int x, int y) const
{
   return vertexMap.find(QPair<int, int>(x, y)).value();
}

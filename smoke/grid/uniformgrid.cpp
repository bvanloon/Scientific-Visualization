#include "uniformgrid.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "grid/cell.h"
#include <QDebug>
#include <assert.h>
#include <QtMath>
#include "grid/utilities/streamlinebuilder.h"
#include <cmath>
#include <QMatrix4x4>
#include <QVector4D>
#include <limits>

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, bool hasPadding) :

   Grid(dimension * dimension, hasPadding),
   dimension(dimension),
   cellSize(computeCellSize(areaSize)),
   padding(0.0f, 0.0f)
{
   if (hasPadding) padding = cellSize;
   this->coveredArea = computeCoveredArea(this->padding, this->cellSize);
}

UniformGrid::UniformGrid(int dimension, QSizeF areaSize, QSizeF padding) :
   Grid(dimension * dimension, true),
   dimension(dimension),
   cellSize(computeCellSize(areaSize, padding)),
   padding(padding)
{
   this->coveredArea = computeCoveredArea(this->padding, this->cellSize);
}

const QVector<QVector3D>& UniformGrid::getVertexPositions() const
{
   return this->vertexPositions;
}

Triangulation UniformGrid::computeTriangulation()
{
   Triangulation triangulation;

   QVector<Cell *>::const_iterator currentCell = cells.begin();

   while (currentCell != cells.end())
   {
      triangulation.extend((*currentCell++)->triangulate());
   }
   return triangulation;
}

void UniformGrid::recomputeVertexPositions(QSizeF oldCellSize, QSizeF newCellSize)
{
   float xScaling = newCellSize.width() / oldCellSize.width();
   float yScaling = newCellSize.height() / oldCellSize.height();

   QMatrix4x4 scaleMatrix;

   scaleMatrix.scale(xScaling, yScaling, 0.0);

   QVector4D transformedPosition;
   for (int i = 0; i < this->numVertices(); i++)
   {
      transformedPosition = scaleMatrix * QVector4D(this->vertexPositions[i], 1.0);
      this->vertexPositions.replace(i, boundToGrid(transformedPosition.toVector3D()));
   }
}

QSizeF UniformGrid::computeCellSize(QSizeF area)
{
   return area / ((float)(dimension + (hasPadding ? 1.0 : -1.0)));
}

QSizeF UniformGrid::computeCellSize(QSizeF area, QSizeF padding)
{
   QSizeF usedArea = area - padding * 2;
   QSizeF cellSize = usedArea / ((float)(dimension - 1));

   return cellSize;
}

QRectF UniformGrid::computeCoveredArea(QSizeF padding, QSizeF cellSize)
{
   QPointF upperLeftCorner = QPointF(padding.width(), padding.height());
   QSizeF size = QSizeF((dimension - 1) * cellSize.width(),
                        (dimension - 1) * cellSize.height());

   return QRectF(upperLeftCorner, size);
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

bool UniformGrid::inGridArea(QVector3D position)
{
   return this->coveredArea.contains(position.x(), position.y());
}

streamobject::Line UniformGrid::computeStreamLine(QVector3D seedPoint,
                                                  Vertex::scalarGetter textureCoordinateGetter,
                                                  Vertex::vectorGetter vectorGetter)
{
   return StreamLineBuilder(this, seedPoint,
                             vectorGetter, textureCoordinateGetter).getStreamLine();
}

StructuredCell *UniformGrid::findCellContaining(QVector3D position)
{
   QPair<int, int> coordinates = findUpperLeftOfContainingCell(position);
   StructuredGridVertex *upperLeftVertex = dynamic_cast<StructuredGridVertex *>(vertexMap.find(coordinates).value());
   Cell *containingCell = upperLeftVertex->getLowerRightCell();

   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);
   return cell;
}

QPair<int,
      int> UniformGrid::findUpperLeftOfContainingCell(QVector3D position)
{
   float xUnrounded = ((float)position.x() - padding.width()) / cellSize.width();
   float yUnrounded = ((float)position.y() - padding.height()) / cellSize.height();
   int x = std::floor(xUnrounded + std::numeric_limits<float>::epsilon());
   int y = std::floor(yUnrounded + std::numeric_limits<float>::epsilon());

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
   QSizeF oldCellSize = cellSize;

   cellSize = computeCellSize(newArea);

   if (hasPadding) padding = cellSize;

   this->coveredArea = computeCoveredArea(this->padding, this->cellSize);
   recomputeVertexPositions(oldCellSize, cellSize);
}

void UniformGrid::changeGridArea(QSizeF newArea, QSizeF padding)
{
   if (hasPadding) this->padding = padding;
   QSizeF oldCellSize = cellSize;
   cellSize = computeCellSize(newArea, padding);
   this->coveredArea = computeCoveredArea(this->padding, this->cellSize);
   recomputeVertexPositions(oldCellSize, cellSize);
}

QVector3D UniformGrid::computeVertexPosition(int i, int j)
{
   return QVector3D(padding.width() + (float)i * cellSize.width(),
                   padding.height() + (float)j * cellSize.height(),
                    0.0f);
}

QVector3D UniformGrid::boundToGrid(QVector3D position)
{
   float offset = std::numeric_limits<float>::epsilon() * 10;

   if (position.x() <= this->coveredArea.left()) position.setX(this->coveredArea.left() + offset);
   if (position.x() >= this->coveredArea.right()) position.setX(this->coveredArea.right() - offset);


   if (position.y() <= this->coveredArea.top()) position.setY(this->coveredArea.top() + offset);
   if (position.y() >= this->coveredArea.bottom()) position.setY(this->coveredArea.bottom() - offset);

   return position;
}

const QSizeF& UniformGrid::getPadding() const
{
   return padding;
}

Vertex *UniformGrid::getVertexAt(int x, int y) const
{
   return vertexMap.find(QPair<int, int>(x, y)).value();
}

#include "simulationgrid.h"

SimulationGrid::SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data) :
   UniformGrid(dimension, areaSize, true),
   data(data)
{
   createVertices();
   createCells();
   createTriangulation();
}

SimulationGrid::~SimulationGrid()
{
   for (auto vertex : vertices) delete vertex;
   vertices.clear();
   vertexPositions.clear();

   for (auto cell : cells) delete cell;
   cells.clear();
}

void SimulationGrid::changeGridArea(QSizeF newArea)
{
   qDebug() << "SimulationGrid::changeGridArea";
   QSizeF oldCellSize = cellSize;
   cellSize    = computeCellSize(newArea);
   if (hasPadding) padding = cellSize;
   coveredArea = computeCoveredArea(padding, cellSize);
   transform(computeScaleMatrix(oldCellSize, cellSize));
}

QSizeF SimulationGrid::computeCellSize(QSizeF gridArea)
{
   return gridArea / ((float)(dimension + (hasPadding ? 1.0 : -1.0)));
}

QMatrix4x4 SimulationGrid::computeScaleMatrix(QSizeF oldCellSize, QSizeF newCellSize)
{
   QMatrix4x4 scaleMatrix;

   float xScaling = newCellSize.width() / oldCellSize.width();
   float yScaling = newCellSize.height() / oldCellSize.height();

   scaleMatrix.scale(xScaling, yScaling, 0.0);
   return scaleMatrix;
}

void SimulationGrid::transform(QMatrix4x4 transformation)
{
   QVector4D transformedPosition;
   for (int i = 0; i < this->numVertices(); i++)
   {
      transformedPosition = transformation * QVector4D(vertexPositions[i], 1.0);
      vertexPositions.replace(i, boundToGrid(transformedPosition.toVector3D()));
   }
   this->triangulation.transform(transformation);
}

void SimulationGrid::createVertices()
{
   for (int y = 0; y < this->dimension; y++)
   {
      for (int x = 0; x < this->dimension; x++)
      {
         this->createVertex(x, y);
      }
   }
}

void SimulationGrid::createVertex(int x, int y)
{
   int idx = this->to1Dindex(x, y);

   const QVector3D *position = this->addVertexPosition(idx, computeVertexPosition(x, y));

   Vertex *vertex            = new SimulationVertex(position,
                                &this->data->getVx()[idx], &this->data->getVy()[idx],
                                &this->data->getFx()[idx], &this->data->getFy()[idx],
                                &this->data->getRho()[idx]);

   this->vertices.replace(idx, vertex);
   this->vertexMap.insert(Index2D(x, y), vertex);
}

const QVector3D *SimulationGrid::addVertexPosition(int idx, QVector3D position)
{
   this->vertexPositions.replace(idx, position);
   return &this->vertexPositions.at(idx);
}

void SimulationGrid::createCells()
{
   for (int x = 0; x < this->dimension - 1; x++)
   {
      for (int y = 0; y < this->dimension - 1; y++)
      {
         createCell(x, y);
      }
   }
}

void SimulationGrid::createCell(int x, int y)
{
   Vertex *leftUpper, *rightLower, *rightUpper, *leftLower;

   leftUpper  = getVertexAt(x, y);
   rightUpper = getVertexAt(x + 1, y);
   leftLower  = getVertexAt(x, y + 1);
   rightLower = getVertexAt(x + 1, y + 1);

   StructuredCell *cell = new StructuredCell(leftUpper, rightUpper, leftLower, rightLower);
   cells.append(cell);

   SimulationVertex *vertex = dynamic_cast<SimulationVertex *>(leftUpper);
   vertex->setLowerRightCell(cells.last());
}

void SimulationGrid::createTriangulation()
{
   QVector<Cell *>::const_iterator cell = cells.begin();
   Triangulation cellTriangulation;

   while (cell != cells.end())
   {
      cellTriangulation = (*cell++)->triangulate();
      triangulation.extend(cellTriangulation);
   }
}

#include "simulationgrid.h"

SimulationGrid::SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data) :
   UniformGrid(dimension, areaSize, true),
   data(data)
{
   addVertices();
   addCells();
}

SimulationGrid::~SimulationGrid()
{
   for (auto vertex : this->vertices)
   {
      delete vertex;
   }
   this->vertices.clear();
   this->vertexPositions.clear();
}

void SimulationGrid::addVertices()
{
   for (int y = 0; y < this->dimension; y++)
   {
      for (int x = 0; x < this->dimension; x++)
      {
         this->addVertex(x, y);
      }
   }
}

void SimulationGrid::addVertex(int x, int y)
{
   int idx = this->to1Dindex(x, y);

   const QVector3D *position = this->addVertexPosition(idx, computeVertexPosition(x, y));

   Vertex *vertex = new SimulationVertex(position,
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

void SimulationGrid::addCells()
{
   Vertex *leftUpper, *rightLower, *rightUpper, *leftLower;
   SimulationVertex *vertex;

   for (int x = 0; x < this->dimension - 1; x++)
   {
      for (int y = 0; y < this->dimension - 1; y++)
      {
         leftUpper = getVertexAt(x, y);
         rightUpper = getVertexAt(x + 1, y);
         leftLower = getVertexAt(x, y + 1);
         rightLower = getVertexAt(x + 1, y + 1);

         this->cells.append(new StructuredCell(leftUpper, rightUpper, leftLower,
                                             rightLower));
         vertex = dynamic_cast<SimulationVertex *>(leftUpper);
         vertex->setLowerRightCell(cells.last());
      }
   }
}

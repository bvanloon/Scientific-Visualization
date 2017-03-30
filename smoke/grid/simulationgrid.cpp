#include "simulationgrid.h"

SimulationGrid::SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data) :
   UniformGrid(dimension, areaSize, true),
   data(data)
{
   addVertices();
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

   QVector3D position = this->computeVertexPosition(x, y);

   this->vertexPositions.replace(idx, position);
   Vertex *vertex = new SimulationVertex(&this->vertexPositions.at(idx),
                                &this->data->getVx()[idx], &this->data->getVy()[idx],
                                &this->data->getFx()[idx], &this->data->getFy()[idx],
                                &this->data->getRho()[idx]);
   this->vertices.replace(idx, vertex);
   this->vertexMap.insert(Index2D(x, y), vertex);
}

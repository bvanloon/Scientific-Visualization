#include "simulationgrid.h"

SimulationGrid::SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data) :
   UniformGrid(dimension, areaSize, true),
   data(data)
{
   addVertices();
}

void SimulationGrid::addVertices()
{
   QVector3D position;
   Vertex *vertex;
   int idx;

   for (int y = 0; y < this->dimension; y++)
   {
      for (int x = 0; x < this->dimension; x++)
      {
         idx = this->to1Dindex(x, y);

         position = this->computeVertexPosition(x, y);
         this->vertexPositions.replace(idx, position);
         vertex = new SimulationVertex(&this->vertexPositions.at(idx),
                                     &this->data->getVx()[idx], &this->data->getVy()[idx],
                                     &this->data->getFx()[idx], &this->data->getFy()[idx],
                                     &this->data->getRho()[idx]);
         this->vertices.replace(idx, vertex);
         this->vertexMap.insert(QPair<int, int>(x, y), vertex);
      }
   }
}

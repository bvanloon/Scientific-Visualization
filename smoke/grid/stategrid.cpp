#include "stategrid.h"

StateGrid::StateGrid(UniformGrid *currentState) :
   UniformGrid(currentState->getDimension(),
               currentState->getCellSize(),
               true,
               currentState->getPadding())
{
   addVertices(currentState);
   addCells(currentState);
}

StateGrid::~StateGrid()
{
   for (auto vertex : this->vertices)
   {
      delete vertex;
   }
}

void StateGrid::addVertices(UniformGrid *currentState)
{
   QList<Index2D> vertexKeys = currentState->getVertexMap().keys();
   Vertex *vertex;
   Index2D key;
   for (int i = 0; i < vertexKeys.length(); i++)
   {
      key = vertexKeys[i];
      vertex = currentState->getVertexMap().find(key).value();
      addVertex(key, dynamic_cast<SimulationVertex *>(vertex));
   }
}

void StateGrid::addVertex(Index2D idx2D, SimulationVertex *vertex)
{
   qDebug() << index << ": " << vertex;
}

void StateGrid::addCells(UniformGrid *currentState)
{}

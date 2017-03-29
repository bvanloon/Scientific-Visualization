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

void StateGrid::addVertices(UniformGrid *currentState)
{
   QList<Index2D> vertexKeys = currentState->getVertexMap().keys();
   Vertex *vertex;
   Index2D key;
   for (int i = 0; i < vertexKeys.length(); i++)
   {
      key = vertexKeys[i];
      vertex = currentState->getVertexMap().find(key).value();
      addVertex(key, dynamic_cast<StructuredGridVertex *>(vertex));
   }
}

void StateGrid::addVertex(Index2D index, StructuredGridVertex *vertex)
{
   qDebug() << index << ": " << vertex;
}

void StateGrid::addCells(UniformGrid *currentState)
{}

#include "stategrid.h"

StateGrid::StateGrid(UniformGrid *currentState) :
   UniformGrid(currentState->getDimension(),
               currentState->getCellSize(),
               true,
               currentState->getPadding()),
   vertexPositions(currentState->numVertices())
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
   Vertex *simulationVertex;
   Index2D key;
   for (int i = 0; i < vertexKeys.length(); i++)
   {
      key = vertexKeys[i];
      simulationVertex = currentState->getVertexMap().find(key).value();
      addVertex(key, dynamic_cast<SimulationVertex *>(simulationVertex));
   }
}

void StateGrid::addVertex(Index2D idx2D, SimulationVertex *vertex)
{
   int idx1D = to1Dindex(idx2D);

   StateVertex *stateVertex = new StateVertex(vertex);

   this->vertexPositions.replace(idx1D, vertex->getPosition());
   this->vertices.replace(idx1D, stateVertex);
   this->vertexMap.insert(idx2D, stateVertex);
}

void StateGrid::addCells(UniformGrid *currentState)
{}

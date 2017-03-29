#include "stategrid.h"

StateGrid::StateGrid(UniformGrid *currentState) :
   UniformGrid(currentState->getDimension(),
               currentState->getCellSize(),
               true,
               currentState->getPadding())
{
    createVertices(currentState);
    createCells(currentState);
}

void StateGrid::createVertices(UniformGrid *currentState)
{
}

void StateGrid::createCells(UniformGrid *currentState)
{

}

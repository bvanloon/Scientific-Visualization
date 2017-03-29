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
}

void StateGrid::addCells(UniformGrid *currentState)
{

}

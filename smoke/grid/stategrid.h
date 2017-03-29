#ifndef STATEGRID_H
#define STATEGRID_H

#include "grid/uniformgrid.h"

class StateGrid : public UniformGrid
{
   public:
      StateGrid(UniformGrid *currentState);

   private:
      void addVertices(UniformGrid *currentState);

      void addVertex(Index2D index, StructuredGridVertex *vertex);

      void addCells(UniformGrid *currentState);
};

#endif // STATEGRID_H

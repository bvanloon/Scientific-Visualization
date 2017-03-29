#ifndef STATEGRID_H
#define STATEGRID_H

#include "grid/uniformgrid.h"

class StateGrid : public UniformGrid
{
   public:
      StateGrid(UniformGrid *currentState);

   private:
      void createVertices(UniformGrid *currentState);

      void createCells(UniformGrid *currentState);
};

#endif // STATEGRID_H

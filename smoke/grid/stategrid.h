#ifndef STATEGRID_H
#define STATEGRID_H

#include "grid/uniformgrid.h"

class StateGrid : public UniformGrid
{
   public:
      StateGrid(UniformGrid *currentState);
      ~StateGrid();

   protected:
      //overwrites the vertexPositions of the parent class.
      QVector<const QVector3D *> vertexPositions;

   private:
      void addVertices(UniformGrid *currentState);

      void addVertex(Index2D index, SimulationVertex *vertex);

      void addCells(UniformGrid *currentState);
};

#endif // STATEGRID_H

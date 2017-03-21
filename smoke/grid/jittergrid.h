#ifndef JITTERGRID_H
#define JITTERGRID_H

#include "grid/uniformgrid.h"

class JitterGrid : public UniformGrid
{
   public:
      JitterGrid(int dimension, QSizeF areaSize, QSizeF padding);

      static UniformGrid *createVisualizationGrid(int dimension, QSizeF size,
                                                  UniformGrid *simulationGrid);

   protected:
      QVector3D computeVertexPosition(int i, int j);

   private:
      std::default_random_engine re;
      double jitterFactor = 0.4;
};

#endif // JITTERGRID_H

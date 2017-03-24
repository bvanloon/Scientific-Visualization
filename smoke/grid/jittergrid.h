#ifndef JITTERGRID_H
#define JITTERGRID_H

#include "grid/uniformgrid.h"
#ifdef __APPLE__
#include <random>
#endif

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
      float jitterFactor = 0.4;
};

#endif // JITTERGRID_H

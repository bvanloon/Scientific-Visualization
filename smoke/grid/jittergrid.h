#ifndef JITTERGRID_H
#define JITTERGRID_H

#include "grid/uniformgrid.h"
#ifdef __APPLE__
#include <random>
#endif

class JitterGrid : public UniformGrid
{
   public:
      JitterGrid(int dimension, QSizeF areaSize, QSizeF padding, double jitterFactor);

      static UniformGrid *createVisualizationGrid(int dimension, QSizeF size, double jitterFactor,
                                                  UniformGrid *simulationGrid);

   protected:
      QVector3D computeVertexPosition(int i, int j);

   private:
      std::default_random_engine re;
      float jitterFactor;
};

#endif // JITTERGRID_H

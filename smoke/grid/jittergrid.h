#ifndef JITTERGRID_H
#define JITTERGRID_H

#include "grid/uniformgrid.h"

class JitterGrid : public UniformGrid
{
   public:
      JitterGrid(int dimension, QSizeF areaSize, QSizeF padding);
};

#endif // JITTERGRID_H

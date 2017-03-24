#ifndef SLICEENGINE_H
#define SLICEENGINE_H

#include "abstractengine.h"

class SliceEngine : public AbstractEngine
{
   public:
      SliceEngine();

      virtual void draw(Simulation *Simulation) = 0;

   private:
      virtual int updateBuffers(Simulation *simulation) = 0;
};

#endif // SLICEENGINE_H

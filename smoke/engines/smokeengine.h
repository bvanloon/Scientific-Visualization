#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"
#include "unused.h"

class SmokeEngine : public AbstractEngine
{
   public:
      SmokeEngine();

      virtual void draw(Simulation *simulation);

   private:
      int fillBuffers(Simulation *UNUSED(simulation));
};


#endif // SMOKEENGINE_H

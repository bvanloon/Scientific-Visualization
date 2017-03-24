#ifndef SMOKESLICESENGINE_H
#define SMOKESLICESENGINE_H

#include "sliceengine.h"
#include <QObject>

class SmokeSlicesEngine : public SliceEngine
{
   public:
      SmokeSlicesEngine();

      virtual void draw(Simulation *simulation);

   private:
      virtual int updateBuffers(Simulation *simulation);
};

#endif // SMOKESLICESENGINE_H

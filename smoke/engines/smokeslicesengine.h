#ifndef SMOKESLICESENGINE_H
#define SMOKESLICESENGINE_H

#include "smokeengine.h"
#include <QObject>

class SmokeSlicesEngine : public SmokeEngine
{
   public:
      SmokeSlicesEngine();

      virtual void draw(Simulation *simulation);

   private:
      virtual int updateBuffers(Simulation *simulation);
};

#endif // SMOKESLICESENGINE_H

#ifndef SMOKESLICESENGINE_H
#define SMOKESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"

class SmokeSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      SmokeSlicesEngine();

      void updateCache();

      void draw(Simulation *simulation);

   private:
      int fillBuffers(Simulation *simulation);
};

#endif // SMOKESLICESENGINE_H

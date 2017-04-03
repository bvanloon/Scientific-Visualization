#ifndef SMOKESLICESENGINE_H
#define SMOKESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"
#include "grid/simulationgrid.h"

class SmokeSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      SmokeSlicesEngine(SimulationGrid *grid);

   protected:
      void updateCache();

   private:
      SimulationGrid *simulation;

      void connectToSettings();
};

#endif // SMOKESLICESENGINE_H

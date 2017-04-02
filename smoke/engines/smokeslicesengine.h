#ifndef SMOKESLICESENGINE_H
#define SMOKESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"
#include "grid/simulationgrid.h"

class SmokeSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      SmokeSlicesEngine(SimulationGrid* grid);

      void updateCache();

      void draw();

   private:
      SimulationGrid *simulation;
};

#endif // SMOKESLICESENGINE_H

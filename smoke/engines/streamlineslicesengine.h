#ifndef STREAMLINESLICESENGINE_H
#define STREAMLINESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"
#include "unused.h"

class StreamLineSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      StreamLineSlicesEngine();

   public slots:

   signals:

   protected:
      void updateCache();

   private:

      GPUData buildStreamLines();

      GPUData buildStreamLine(const SimulationGrid *grid, QPointF seedPoint);

      void connectToSettings();
};

#endif // STREAMLINESLICESENGINE_H

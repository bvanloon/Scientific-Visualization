#ifndef STREAMLINESLICESENGINE_H
#define STREAMLINESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"
#include "unused.h"

class StreamLineSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      StreamLineSlicesEngine(UniformGrid *simulationGrid);

   public slots:

   signals:

   protected:
      void updateCache();

   private:

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      void connectToSettings();

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H

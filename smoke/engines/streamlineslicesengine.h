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

      void updateCache();

      void drawSlice(GPUData data);

   public slots:

   signals:

   private:

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H

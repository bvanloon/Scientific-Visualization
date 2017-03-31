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

      virtual void draw(Simulation *UNUSED(simulation));

      void drawSlice(GPUData data);

   public slots:

   signals:

   private:

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      int fillBuffers(Simulation *UNUSED(Simulation));

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H

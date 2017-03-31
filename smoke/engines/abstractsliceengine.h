#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "utilities/sizelimitedqueue.h"

class AbstractSliceEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel);

      virtual void draw(Simulation *Simulation) = 0;

   public slots:
      void onUpdateModelViewMatrix();

   private:

      SizeLimitedQueue<GPUData> slices;

      virtual int updateBuffers(Simulation *simulation) = 0;

      void updateModelViewMatrix();
};

#endif // ABSTRACTSLICEENGINE_H

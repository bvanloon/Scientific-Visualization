#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "utilities/sizelimitedqueue.h"

class AbstractSliceEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType);

      virtual void draw(Simulation *Simulation) = 0;

   public slots:
      void onUpdateModelViewMatrix();

      void onNumberOfSlicesChanged(int newNumberOfSlices);

   private:

      SizeLimitedQueue<GPUData> slices;

      virtual int updateBuffers(Simulation *simulation) = 0;

      void updateModelViewMatrix();

      virtual void connectToSettings();
};

#endif // ABSTRACTSLICEENGINE_H

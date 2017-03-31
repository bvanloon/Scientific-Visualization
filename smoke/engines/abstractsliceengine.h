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

      void onClearCache(Settings::engines::EnginesTypes engine);
      void onClearCache();

   private:

      SizeLimitedQueue<GPUData> cache;

      virtual int updateBuffers(Simulation *simulation) = 0;

      void updateModelViewMatrix();

      virtual void connectToSettings();
      virtual void connectToColorMap();

      void clearCache();
};

#endif // ABSTRACTSLICEENGINE_H

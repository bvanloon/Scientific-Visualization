#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "unused.h"
#include "utilities/sizelimitedqueue.h"

class AbstractSliceEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType);

      void draw(Simulation *UNUSED(Simulation));

   public slots:
      void onUpdateModelViewMatrix();

      void onNumberOfSlicesChanged(int newNumberOfSlices);

      void onClearCache(Settings::engines::EnginesTypes engine);
      void onClearCache();

   protected:
      SizeLimitedQueue<GPUData> cache;

      void updateBuffers(GPUData data);
      void drawSlices();

      virtual void updateCache() = 0;

   private:
      void updateModelViewMatrix();

      int fillBuffers(Simulation *UNUSED(simulation));

      virtual void connectToSettings();
      virtual void connectToColorMap();

      void clearCache();
};

#endif // ABSTRACTSLICEENGINE_H

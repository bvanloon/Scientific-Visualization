#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include <QMatrix4x4>
#include "abstract3Dengine.h"
#include "unused.h"
#include "utilities/sizelimitedqueue.h"

class AbstractSliceEngine : public Abstract3DEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType);

      void draw();

   public slots:

      void onNumberOfSlicesChanged(int newNumberOfSlices);

      void onNewSimulationState();

      void onNumberOfStatesPerSliceChanged(int UNUSED(numStatesPerSlice));

      void onGLobalAlphaChanged(double globalAlpha);

      void onClearCache(Settings::engines::EnginesTypes engine);
      void onClearCache();

   protected:
      SizeLimitedQueue<GPUData> cache;

      virtual void updateCache() = 0;

      void clearCache();

   private:
      static const double maximumZTranslation;
      static const double minimumZTranslation;

      int numRecentSimulationStatesNotInSlice;

      void drawSlices();

      double computeTranslationStepSize();

      void updateBuffers(GPUData data);

      void connectToSettings();

      virtual void connectToColorMap();
};

#endif // ABSTRACTSLICEENGINE_H

#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include <QMatrix4x4>
#include "abstractengine.h"
#include "unused.h"
#include "utilities/sizelimitedqueue.h"

class AbstractSliceEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType);

      void draw();

   public slots:
      void onUpdateModelViewMatrix();

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

      void updateModelViewMatrix(QMatrix4x4 modelMatrix = QMatrix4x4());

      QMatrix4x4 computeViewMatrix();

      double computeTranslationStepSize();

      void updateBuffers(GPUData data);

      void connectToSettings();

      virtual void connectToColorMap();
};

#endif // ABSTRACTSLICEENGINE_H
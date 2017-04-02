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
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType, QMatrix4x4 toSliceTransformation);
      AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType);

      void draw();

   public slots:
      void onUpdateModelViewMatrix();

      void onNumberOfSlicesChanged(int newNumberOfSlices);

      void onNewSimulationState();

      void onClearCache(Settings::engines::EnginesTypes engine);
      void onClearCache();

   protected:
      SizeLimitedQueue<GPUData> cache;
      QMatrix4x4 toSliceTransformation;

      virtual void updateCache() = 0;

      QMatrix4x4 computeToSliceTransformation();

   private:
      static const double maximumYTranslation;
      static const double minimumYTranslation;

      void drawSlices();

      void updateModelViewMatrix();

      QMatrix4x4 computeModuleViewMatrix();

      double computeTranslationStepSize();

      void updateBuffers(GPUData data);

      int fillBuffers(Simulation *UNUSED(simulation));

      void connectToSettings();

      virtual void connectToColorMap();

      void clearCache();
};

#endif // ABSTRACTSLICEENGINE_H

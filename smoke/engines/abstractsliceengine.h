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

      void draw(Simulation *UNUSED(Simulation));

   public slots:
      void onUpdateModelViewMatrix();

      void onNumberOfSlicesChanged(int newNumberOfSlices);

      void onNewSimulationState();

      void onClearCache(Settings::engines::EnginesTypes engine);
      void onClearCache();

   protected:
      SizeLimitedQueue<GPUData> cache;
      QMatrix4x4 toSliceTransformation;

      void updateBuffers(GPUData data);

      void drawSlices();

      virtual void updateCache() = 0;

      virtual void connectToSettings();

   private:
      void updateModelViewMatrix();


      static const double maximumYTranslation;
      QMatrix4x4 computeModuleViewMatrix();

      double computeTranslationStepSize();

      int fillBuffers(Simulation *UNUSED(simulation));

      virtual void connectToColorMap();

      void defineToSliceTransformation();

      void clearCache();
};

#endif // ABSTRACTSLICEENGINE_H

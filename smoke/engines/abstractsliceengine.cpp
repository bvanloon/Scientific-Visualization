#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

const double AbstractSliceEngine::maximumZTranslation = -850;
const double AbstractSliceEngine::minimumZTranslation = 0.0;

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType) :
   Abstract3DEngine(lightModel, engineType),
   cache(Settings::visualization::slices().numSlices)
{
   updateModelViewMatrix();
   connectToSettings();
}

void AbstractSliceEngine::draw()
{
   drawSlices();
}

void AbstractSliceEngine::onUpdateModelViewMatrix()
{
   updateModelViewMatrix();
}

void AbstractSliceEngine::onNumberOfSlicesChanged(int newNumberOfSlices)
{
   cache.changeMaximumSize(newNumberOfSlices);
}

void AbstractSliceEngine::onNewSimulationState()
{
   numRecentSimulationStatesNotInSlice++;
   if (numRecentSimulationStatesNotInSlice >= Settings::visualization::slices().numStatesPerSlice)
   {
      updateCache();
      numRecentSimulationStatesNotInSlice = 0;
   }
}

void AbstractSliceEngine::onNumberOfStatesPerSliceChanged(int UNUSED(numStatesPerSlice))
{
   clearCache();
}

void AbstractSliceEngine::onGLobalAlphaChanged(double globalAlpha)
{
   setGlobalAlpha(globalAlpha);
}

void AbstractSliceEngine::onClearCache(Settings::engines::EnginesTypes engine)
{
   if (engine == me) clearCache();
}

void AbstractSliceEngine::onClearCache()
{
   clearCache();
}

void AbstractSliceEngine::clearCache()
{
   cache.clear();
}

void AbstractSliceEngine::updateModelViewMatrix(QMatrix4x4 modelMatrix)
{
   this->setModelViewMatrix(computeViewMatrix() * modelMatrix);
}

QMatrix4x4 AbstractSliceEngine::computeViewMatrix()
{
   QMatrix4x4 viewMatrix = QMatrix4x4();

   viewMatrix.translate(Settings::canvas().panningPosition);

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   viewMatrix *= rotationMatrix;

   viewMatrix.scale(Settings::canvas().scalingFactor);
   return viewMatrix;
}

void AbstractSliceEngine::updateBuffers(GPUData data)
{
   AbstractEngine::updateBuffers(data);
}

void AbstractSliceEngine::drawSlices()
{
   QMatrix4x4 modelMatrix;
   double translationStep = computeTranslationStepSize();

   for (GPUData data : cache)
   {
      updateModelViewMatrix(modelMatrix);
      updateBuffersAndDraw(data);
      modelMatrix.translate(0.0, 0.0, translationStep);
   }
}

double AbstractSliceEngine::computeTranslationStepSize()
{
   double numSlices = static_cast<double>(Settings::visualization::slices().numSlices);
   return (maximumZTranslation - minimumZTranslation) / (numSlices - 1);
}

void AbstractSliceEngine::connectToSettings()
{
   connect(&Settings::visualization::slices(), SIGNAL(numberOfSlicesChanged(int)),
           this, SLOT(onNumberOfSlicesChanged(int)));
   connect(&Settings::visualization::slices(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
   connect(&Settings::visualization::slices(), SIGNAL(numberOfSlicesChanged(int)),
           this, SLOT(onNumberOfSlicesChanged(int)));
   connect(&Settings::canvas(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
   connect(&Settings::canvas(), SIGNAL(clearCache(Settings::engines::EnginesTypes)),
           this, SLOT(onClearCache(Settings::engines::EnginesTypes)));
   connect(&Settings::visualization::slices(), SIGNAL(globalALphaChanged(double)),
           this, SLOT(onGLobalAlphaChanged(double)));
   connect(&Settings::visualization::slices(), SIGNAL(numberOfStatesPerSliceChanged(int)),
           this, SLOT(onNumberOfStatesPerSliceChanged(int)));
}

void AbstractSliceEngine::connectToColorMap()
{
   AbstractEngine::connectToColorMap();
   connect(this->colorMap, SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

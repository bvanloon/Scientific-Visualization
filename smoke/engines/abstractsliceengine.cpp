#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

const double AbstractSliceEngine::maximumYTranslation = 1.7;
const double AbstractSliceEngine::minimumYTranslation = 0.0;

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel,
                                         Settings::engines::EnginesTypes engineType,
                                         QMatrix4x4 toSliceTransformation) :
   AbstractEngine(lightModel, engineType),
   cache(Settings::visualization::slices().numberOfSlices),
   toSliceTransformation(toSliceTransformation)
{
   updateModelViewMatrix();
   connectToSettings();
}

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel, Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType),
   cache(Settings::visualization::slices().numberOfSlices),
   toSliceTransformation(computeToSliceTransformation())
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
   updateCache();
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

QMatrix4x4 AbstractSliceEngine::computeToSliceTransformation()
{
   QMatrix4x4 transform;
   QVector3D xaxis = QVector3D(1.0, 0.0, 0.0);
   QVector3D yaxis = QVector3D(0.0, 1.0, 0.0);

   transform.scale(0.76);
   transform.rotate(45, yaxis);
   transform.rotate(80, xaxis);
   return transform;
}

void AbstractSliceEngine::clearCache()
{
   cache.clear();
}

void AbstractSliceEngine::updateModelViewMatrix()
{
   this->setModelViewMatrix(computeModuleViewMatrix());
}

QMatrix4x4 AbstractSliceEngine::computeModuleViewMatrix()
{
   QMatrix4x4 modelViewMatrix = QMatrix4x4();

   modelViewMatrix.translate(Settings::canvas().panningPosition);

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   modelViewMatrix *= rotationMatrix;

   modelViewMatrix.scale(Settings::canvas().scalingFactor);
   return modelViewMatrix;
}

int AbstractSliceEngine::fillBuffers(Simulation *UNUSED(simulation))
{
   std::logic_error("AbstractSliceEngine::fillBuffers is only implemented to ensure compliance with legacy code.");
   return 0;
}

void AbstractSliceEngine::updateBuffers(GPUData data)
{
   AbstractEngine::updateBuffers(data);
}

void AbstractSliceEngine::drawSlices()
{
   QMatrix4x4 transform;
   double yTranslationStep = computeTranslationStepSize();

   for (GPUData data : cache)
   {
      setScreenSpaceTransformation(transform);
      updateBuffersAndDraw(data);
      transform.translate(0.0, yTranslationStep, 0.0);
   }
}

double AbstractSliceEngine::computeTranslationStepSize()
{
   double numSlices = static_cast<double>(Settings::visualization::slices().numberOfSlices);
   return (maximumYTranslation - minimumYTranslation) / (numSlices - 1);
}

void AbstractSliceEngine::connectToSettings()
{
   connect(&Settings::visualization::slices(), SIGNAL(numberOfSlicesChanged(int)),
           this, SLOT(onNumberOfSlicesChanged(int)));
   connect(&Settings::canvas(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
   connect(&Settings::canvas(), SIGNAL(clearCache(Settings::engines::EnginesTypes)),
           this, SLOT(onClearCache(Settings::engines::EnginesTypes)));
   connect(&Settings::visualization::slices(), SIGNAL(globalALphaChanged(double)),
           this, SLOT(onGLobalAlphaChanged(double)));
}

void AbstractSliceEngine::connectToColorMap()
{
   AbstractEngine::connectToColorMap();
   connect(this->colorMap, SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

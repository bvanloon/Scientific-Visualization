#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

const double AbstractSliceEngine::maximumYTranslation = 1.7;

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel,
                                         Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType),
   cache(Settings::visualization::slices().numberOfSlices)
{
   defineToSliceTransformation();

   updateModelViewMatrix();
   connectToSettings();
}

void AbstractSliceEngine::defineToSliceTransformation()
{
   QVector3D xaxis = QVector3D(1.0, 0.0, 0.0);
   QVector3D yaxis = QVector3D(0.0, 1.0, 0.0);

   toSliceTransformation.scale(0.76);
   toSliceTransformation.rotate(45, yaxis);
   toSliceTransformation.rotate(80, xaxis);
}

void AbstractSliceEngine::draw(Simulation *UNUSED(Simulation))
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
   return maximumYTranslation / (numSlices - 1);
}

void AbstractSliceEngine::connectToSettings()
{
   connect(&Settings::visualization::slices(), SIGNAL(numberOfSlicesChanged(int)),
           this, SLOT(onNumberOfSlicesChanged(int)));
   connect(&Settings::canvas(), SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
   connect(&Settings::canvas(), SIGNAL(clearCache(Settings::engines::EnginesTypes)),
           this, SLOT(onClearCache(Settings::engines::EnginesTypes)));
}

void AbstractSliceEngine::connectToColorMap()
{
   AbstractEngine::connectToColorMap();
   connect(this->colorMap, SIGNAL(clearCache()),
           this, SLOT(onClearCache()));
}

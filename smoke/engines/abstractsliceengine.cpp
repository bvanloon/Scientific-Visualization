#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

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

   toSliceTransformation.translate(0.0, 20.0, 0.0);
   toSliceTransformation.rotate(40, yaxis);
   toSliceTransformation.rotate(80, xaxis);
}

void AbstractSliceEngine::draw(Simulation *UNUSED(Simulation))
{
   updateCache();
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
   QMatrix4x4 newModelViewMatrix = computeModuleViewMatrix();
   this->modelViewMatrix = newModelViewMatrix;
   this->setMVPMatrix();
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
   int bufferLength;
   for (GPUData data : cache)
   {
      bufferLength = data.numElements();
      updateBuffers(data);
      drawWithMode(data.getDrawMode(), bufferLength);
   }
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

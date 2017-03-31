#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel,
                                         Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType),
   cache(Settings::visualization::slices().numberOfSlices)
{
   updateModelViewMatrix();
   connectToSettings();
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
   this->modelViewMatrix = QMatrix4x4();

   this->modelViewMatrix.translate(Settings::canvas().panningPosition);

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   this->modelViewMatrix *= rotationMatrix;

   this->modelViewMatrix.scale(Settings::canvas().scalingFactor);

   this->setMVPMatrix();
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

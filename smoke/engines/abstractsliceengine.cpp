#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel,
                                         Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType),
   slices(Settings::visualization::slices().numberOfSlices)
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
   slices.changeMaximumSize(newNumberOfSlices);
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
}

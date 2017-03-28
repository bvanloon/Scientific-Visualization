#include "abstractsliceengine.h"
#include "settings/canvassettings.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel) :
   AbstractEngine(lightModel)
{
   updateModelViewMatrix();
}

void AbstractSliceEngine::onUpdateModelViewMatrix()
{
   updateModelViewMatrix();
}

void AbstractSliceEngine::updateModelViewMatrix()
{
   this->modelViewMatrix = QMatrix4x4();

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   this->modelViewMatrix *= rotationMatrix;

   this->modelViewMatrix.scale(Settings::canvas().scalingFactor);

   this->setMVPMatrix();
}

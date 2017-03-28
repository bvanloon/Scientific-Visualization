#include "abstractsliceengine.h"
#include "settings/canvassettings.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel) :
   AbstractEngine(lightModel)
{}

void AbstractSliceEngine::onUpdateModelViewMatrix()
{
   this->modelViewMatrix = QMatrix4x4();

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   this->modelViewMatrix *= rotationMatrix;

   //Do things with the  scale of the model view matrix;

   this->setMVPMatrix();
}

#include "abstractsliceengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel) :
   AbstractEngine(lightModel),
   slices(Settings::visualization::slices().numberOfSlices)
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

   this->modelViewMatrix.translate(Settings::canvas().panningPosition);

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   this->modelViewMatrix *= rotationMatrix;

   this->modelViewMatrix.scale(Settings::canvas().scalingFactor);

   this->setMVPMatrix();
}

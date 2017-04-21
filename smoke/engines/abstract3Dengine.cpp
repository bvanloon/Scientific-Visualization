#include "abstract3Dengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

const double Abstract3DEngine::maximumZTranslation = -850;
const double Abstract3DEngine::minimumZTranslation = 0.0;

Abstract3DEngine::Abstract3DEngine(AbstractEngine::lightModel lightModel,
                                   Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType)
{
   updateModelViewMatrix();
   connectToSettings();
}

void Abstract3DEngine::onUpdateModelViewMatrix()
{
   updateModelViewMatrix();
}

void Abstract3DEngine::updateModelViewMatrix(QMatrix4x4 modelMatrix)
{
   this->setModelViewMatrix(computeViewMatrix() * modelMatrix);
}

QMatrix4x4 Abstract3DEngine::computeViewMatrix()
{
   QMatrix4x4 viewMatrix = QMatrix4x4();

   viewMatrix.translate(Settings::canvas().panningPosition);

   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   viewMatrix *= rotationMatrix;

   viewMatrix.scale(Settings::canvas().scalingFactor);
   return viewMatrix;
}

void Abstract3DEngine::connectToSettings()
{
   connect(&Settings::canvas(), SIGNAL(updateModelViewMatrix()),
            this, SLOT(onUpdateModelViewMatrix()));
}

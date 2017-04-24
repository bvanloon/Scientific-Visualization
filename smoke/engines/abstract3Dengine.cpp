#include "abstract3Dengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

const Range<double> Abstract3DEngine::zTranslationRange = Range<double>(0.0, -850);

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
   QMatrix4x4 toOriginTransform = toOriginTranslation();

   QMatrix4x4 viewMatrix = QMatrix4x4();

   //Pan from original position
   viewMatrix.translate(Settings::canvas().panningPosition);

   //Place back at original position
   viewMatrix *= toOriginTransform.inverted();

   //Rotate
   QMatrix4x4 rotationMatrix = Settings::canvas().rotation.matrix();
   viewMatrix *= rotationMatrix;

   //Scale
   viewMatrix.scale(Settings::canvas().scalingFactor);

   //Place at origin
   viewMatrix *= toOriginTransform;

   return viewMatrix;
}

QMatrix4x4 Abstract3DEngine::toOriginTranslation()
{
   QMatrix4x4 transform;
   QVector3D translation = QVector3D(
               Settings::canvas().size.width(),
               Settings::canvas().size.height(),
               zTranslationRange.length());
   translation /= 2;
   translation *= -1;
   transform.translate(translation);
   return transform;
}

void Abstract3DEngine::connectToSettings()
{
   connect(&Settings::canvas(), SIGNAL(updateModelViewMatrix()),
            this, SLOT(onUpdateModelViewMatrix()));
}

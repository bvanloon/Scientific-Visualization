#include "abstract3Dengine.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

Abstract3DEngine::Abstract3DEngine(AbstractEngine::lightModel lightModel,
                                   Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType)
{
   qDebug() << "Abstract3DEngine::Abstract3DEngine: Call updateModelViewMatrix.";
   qDebug() << "Abstract3DEngine::Abstract3DEngine: Call connectToSettings().";
//    updateModelViewMatrix();
//    connectToSettings();
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

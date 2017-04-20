#include "abstract3Dengine.h"

Abstract3DEngine::Abstract3DEngine(AbstractEngine::lightModel lightModel,
                                   Settings::engines::EnginesTypes engineType) :
   AbstractEngine(lightModel, engineType)
{
   qDebug() << "Abstract3DEngine::Abstract3DEngine: Call updateModelViewMatrix.";
   qDebug() << "Abstract3DEngine::Abstract3DEngine: Call connectToSettings().";
//    updateModelViewMatrix();
//    connectToSettings();
}

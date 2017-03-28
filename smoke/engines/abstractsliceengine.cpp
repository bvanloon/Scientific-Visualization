#include "abstractsliceengine.h"

AbstractSliceEngine::AbstractSliceEngine(AbstractEngine::lightModel lightModel) :
   AbstractEngine(lightModel)
{}

void AbstractSliceEngine::onRotationChanged(int direction, int newAngle)
{
   qDebug() << "AbstractSliceEngine::onRotationChanged: direction: " << direction << " angle: " << newAngle;
}

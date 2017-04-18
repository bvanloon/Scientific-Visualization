#include "streamobject.h"
#include <QDebug>

StreamObject::StreamObject(QObject *parent) :
   QObject(parent),
   timeStep(1.0)
{}

void StreamObject::ontimeStepChanged(double newTimeStep)
{
   this->timeStep = newTimeStep;
   emit clearCache();
}

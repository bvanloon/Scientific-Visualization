#include "streamobject.h"
#include <QDebug>

StreamObject::StreamObject(QObject *parent) :
   QObject(parent),
   timeStep(1.0),
   maximumTime(100)
{}

void StreamObject::ontimeStepChanged(double newTimeStep)
{
   this->timeStep = newTimeStep;
   emit clearCache();
}

void StreamObject::onMaximumTimeChanged(double newMaximumTime)
{
   this->maximumTime = newMaximumTime;
   emit clearCache();
}

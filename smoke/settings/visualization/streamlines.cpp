#include "streamlines.h"
#include "settings/visualizationsettings.h"

Settings::visualization::StreamLines::StreamLines(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   timeStep(1.0),
   edgeLengthFactor(0.5)
{}

const Settings::visualization::StreamLines& Settings::visualization::StreamLines::instance()
{
   static StreamLines instance;

   return instance;
}

void Settings::visualization::StreamLines::ontimeStepChanged(double newTimeStep)
{
   this->timeStep = newTimeStep;
}

void Settings::visualization::StreamLines::onEdgeLengthFactorChanged(double newFactor)
{
   this->edgeLengthFactor = newFactor;
}

void Settings::visualization::StreamLines::onClearSeedPoints()
{
    qDebug() << "Settings::visualization::StreamLines::onClearSeedPoints implement";
}

void Settings::visualization::StreamLines::onSeedPointAdded(QPointF newSeedPoint)
{
    this->seedPoints.append(newSeedPoint);
}

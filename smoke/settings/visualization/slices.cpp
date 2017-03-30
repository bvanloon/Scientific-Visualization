#include "slices.h"

Settings::visualization::Slices::Slices(QObject *parent) :
   QObject(parent),
   globalAlpha(1.0),
   numberOfSlices(10)
{
   connectToOtherSettings();
}

void Settings::visualization::Slices::connectToOtherSettings()
{}

const Settings::visualization::Slices& Settings::visualization::Slices::instance()
{
   static Slices instance;

   return instance;
}

void Settings::visualization::Slices::onNumberOfSlicesChanged(int newNumberOfSlices)
{
   this->numberOfSlices = newNumberOfSlices;
   emit numberOfSlicesChanged(newNumberOfSlices);
}

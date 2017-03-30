#include "slices.h"

Settings::visualization::Slices::Slices(QObject *parent) :
   QObject(parent)
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

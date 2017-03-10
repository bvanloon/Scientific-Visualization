#include "settings/visualizationsettings.h"

const Settings::visualization::Smoke& Settings::visualization::Smoke::instance()
{
   static Smoke instance;

   return instance;
}

Settings::visualization::Smoke::Smoke(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap())
{}

Settings::visualization::ColorMap *Settings::visualization::Smoke::getColorMap() const
{
   return colorMap;
}

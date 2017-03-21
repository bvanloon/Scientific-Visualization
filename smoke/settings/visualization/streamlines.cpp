#include "streamlines.h"
#include "settings/visualizationsettings.h"

Settings::visualization::StreamLines::StreamLines(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap())
{}

const Settings::visualization::StreamLines& Settings::visualization::StreamLines::instance()
{
   static StreamLines instance;

   return instance;
}

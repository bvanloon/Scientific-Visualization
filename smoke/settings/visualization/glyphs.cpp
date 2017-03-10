#include "settings/visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   vectorScale(10),
   colorMap(new ColorMap())
{}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

Settings::visualization::ColorMap *Settings::visualization::Glyphs::getColorMap() const
{
   return colorMap;
}

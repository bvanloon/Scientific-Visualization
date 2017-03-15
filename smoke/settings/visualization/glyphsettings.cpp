#include "settings/visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   vectorScale(1000)
{
   vectorGetter = Vertex::getVectorGetter(Settings::defaults::visualization::glyphs::vector);
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

void Settings::visualization::Glyphs::onVectorFieldChanged(Settings::sim::Vector vectorField)
{
   vectorGetter = Vertex::getVectorGetter(vectorField);
}

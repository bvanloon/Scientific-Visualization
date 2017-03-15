#include "../visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::ColorMap::ColorMap(QObject *parent) :
   QObject(parent),
   scalar(Settings::sim::Scalar::fluidDensity)
{
   textureGetter = Vertex::getScalarGetter(Settings::defaults::visualization::colormap::scalar);
}

void Settings::visualization::ColorMap::onTextureVariableChanged(sim::Scalar scalarVariable)
{
   this->scalar = scalarVariable;
   this->textureGetter = Vertex::getScalarGetter(scalarVariable);
   QPair<float, float> range = Settings::simulation().getRange(scalarVariable);
   emit valueRangeChanged(scalarVariable, range.first, range.second);
}

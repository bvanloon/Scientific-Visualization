#include "../visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::ColorMap::ColorMap(QObject *parent) :
   QObject(parent),
   scalar(Settings::sim::Scalar::fluidDensity),
   textureGetter(&Vertex::getFluidDensity)
{}

void Settings::visualization::ColorMap::onTextureVariableChanged(sim::Scalar scalarVariable)
{
   qDebug() << "Settings::visualization::ColorMap::onTextureVariableChanged: " << scalarVariable;
   this->scalar = scalarVariable;
   this->textureGetter = getTextureGetter(scalarVariable);
   QPair<float, float> range = Settings::simulation().getRange(scalarVariable);
   emit valueRangeChanged(scalarVariable, range.first, range.second);
}

Vertex::scalarGetter Settings::visualization::ColorMap::getTextureGetter(Settings::sim::Scalar scalarVariable)
{
   switch (scalarVariable)
   {
   case Settings::sim::fluidDensity:
      return &Vertex::getFluidDensity;

   case Settings::sim::fluidVelocityMagnitude:
      return &Vertex::getFluidVelocityMagnitude;

   case Settings::sim::forceFieldMagnitude:
      return &Vertex::getForceMagnitude;
   }
}

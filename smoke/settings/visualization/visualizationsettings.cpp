#include "../visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::VisualizationClassOld::VisualizationClassOld(QObject *parent) :
   QObject(parent),
   textureGetter(&::Simulation::getTexCoordFluidDensity),
   scalar(::Settings::sim::Scalar::fluidDensity)
{}

void Settings::VisualizationClassOld::setScalarVariableToFluidDensity()
{
   this->textureGetter = &::Simulation::getTexCoordFluidDensity;
   this->scalar = Settings::sim::Scalar::fluidDensity;
   emit valueRangeChangedOld(0.0f, Settings::simulation().force);
}

void Settings::VisualizationClassOld::setScalarVariableToFluidVelocityMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
   this->scalar = Settings::sim::Scalar::fluidVelocityMagnitude;
   emit valueRangeChangedOld(Settings::simulation().fluidVelocityMagnitudeMinimum,
                          Settings::simulation().fluidVelocityMagnitudeMaximum);
}

void Settings::VisualizationClassOld::setScalarVariableToForceFieldMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
   this->scalar = Settings::sim::Scalar::forceFieldMagnitude;
   emit valueRangeChangedOld(Settings::simulation().forceFieldMagnitudeMinimum,
                          Settings::simulation().forceFieldMagnitudeMaximum);
}

const Settings::VisualizationClassOld& Settings::VisualizationClassOld::instance()
{
   static VisualizationClassOld instance;

   return instance;
}

void Settings::VisualizationClassOld::onTextureVariableChangedOld(sim::Scalar scalarVariable)
{
   switch (scalarVariable)
   {
   case Settings::sim::Scalar::fluidDensity:
      setScalarVariableToFluidDensity();
      break;

   case Settings::sim::Scalar::fluidVelocityMagnitude:
      setScalarVariableToFluidVelocityMagnitude();
      break;

   case Settings::sim::Scalar::forceFieldMagnitude:
      setScalarVariableToForceFieldMagnitude();
      break;

   default:
      qDebug() << "Invalid scalar variable, going with the default: fluidDensity.";
      setScalarVariableToFluidDensity();
      break;
   }
}


Settings::visualization::ColorMap::ColorMap(QObject *parent) :
    QObject(parent),
    scalar(Settings::sim::Scalar::fluidDensity)
{}

void Settings::visualization::ColorMap::onTextureVariableChanged(sim::Scalar scalarVariable)
{
    qDebug() << "Settings::visualization::ColorMap::onTextureVariableChanged: " << scalarVariable;
}

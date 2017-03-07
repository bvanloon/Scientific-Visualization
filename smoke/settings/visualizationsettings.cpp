#include "visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::Visualization::Visualization(QObject *parent) :
   QObject(parent),
   textureGetter(&::Simulation::getTexCoordFluidDensity),
   scalar(ScalarVariable::fluidDensity),
   vectorScale(10)
{
}


void Settings::Visualization::setScalarVariableToFluidDensity()
{
   this->textureGetter = &::Simulation::getTexCoordFluidDensity;
   this->scalar = Settings::Visualization::ScalarVariable::fluidDensity;
   emit valueRangeChanged(0.0f, Settings::simulation().force);
}


void Settings::Visualization::setScalarVariableToFluidVelocityMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
   this->scalar = Settings::Visualization::ScalarVariable::fluidVelocityMagnitude;
   emit valueRangeChanged(Settings::simulation().fluidVelocityMagnitudeMinimum,
                          Settings::simulation().fluidVelocityMagnitudeMaximum);
}


void Settings::Visualization::setScalarVariableToForceFieldMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
   this->scalar = Settings::Visualization::ScalarVariable::forceFieldMagnitude;
   emit valueRangeChanged(Settings::simulation().forceFieldMagnitudeMinimum,
                          Settings::simulation().forceFieldMagnitudeMaximum);
}


const Settings::Visualization& Settings::Visualization::instance()
{
   static Visualization instance;

   return instance;
}


QStringList Settings::Visualization::getScalarVariableNames()
{
   QStringList scalarVariableNames;

   scalarVariableNames << "Fluid density"
                       << "Fluid velocity magnitude"
                       << "Force field magnitude";
   return scalarVariableNames;
}


void Settings::Visualization::onScalarVariableChanged(Settings::Visualization::ScalarVariable scalarVariable)
{
   switch (scalarVariable)
   {
   case fluidDensity:
      setScalarVariableToFluidDensity();
      break;

   case fluidVelocityMagnitude:
      setScalarVariableToFluidVelocityMagnitude();
      break;

   case forceFieldMagnitude:
      setScalarVariableToForceFieldMagnitude();
      break;

   default:
      qDebug() << "Invalid scalar variable, going with the default: fluidDensity.";
      setScalarVariableToFluidDensity();
      break;
   }
}

#include "visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::Visualization::Visualization(QObject *parent) :
   QObject(parent),
   textureGetter(&::Simulation::getTexCoordFluidDensity),
   scalar(visualization::ScalarVariable::fluidDensity),
   vectorScale(10)
{}

void Settings::Visualization::setScalarVariableToFluidDensity()
{
   this->textureGetter = &::Simulation::getTexCoordFluidDensity;
   this->scalar = Settings::visualization::ScalarVariable::fluidDensity;
   emit valueRangeChanged(0.0f, Settings::simulation().force);
}

void Settings::Visualization::setScalarVariableToFluidVelocityMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
   this->scalar = Settings::visualization::ScalarVariable::fluidVelocityMagnitude;
   emit valueRangeChanged(Settings::simulation().fluidVelocityMagnitudeMinimum,
                          Settings::simulation().fluidVelocityMagnitudeMaximum);
}

void Settings::Visualization::setScalarVariableToForceFieldMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
   this->scalar = Settings::visualization::ScalarVariable::forceFieldMagnitude;
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

void Settings::Visualization::onScalarVariableChanged(Settings::visualization::ScalarVariable scalarVariable)
{
   switch (scalarVariable)
   {
   case Settings::visualization::fluidDensity:
      setScalarVariableToFluidDensity();
      break;

   case Settings::visualization::fluidVelocityMagnitude:
      setScalarVariableToFluidVelocityMagnitude();
      break;

   case Settings::visualization::forceFieldMagnitude:
      setScalarVariableToForceFieldMagnitude();
      break;

   default:
      qDebug() << "Invalid scalar variable, going with the default: fluidDensity.";
      setScalarVariableToFluidDensity();
      break;
   }
}

const Settings::visualization::Smoke& Settings::visualization::Smoke::instance()
{
   static Smoke instance;

   return instance;
}

Settings::visualization::Smoke::Smoke(QObject *parent) :
   QObject(parent)
{}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent)
{}

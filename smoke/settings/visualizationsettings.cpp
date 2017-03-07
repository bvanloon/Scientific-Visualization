#include "visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::VisualizationClassOld::VisualizationClassOld(QObject *parent) :
   QObject(parent),
   textureGetter(&::Simulation::getTexCoordFluidDensity),
   scalar(visualization::ScalarVariable::fluidDensity),
   vectorScale(10)
{}

void Settings::VisualizationClassOld::setScalarVariableToFluidDensity()
{
   this->textureGetter = &::Simulation::getTexCoordFluidDensity;
   this->scalar = Settings::visualization::ScalarVariable::fluidDensity;
   emit valueRangeChanged(0.0f, Settings::simulation().force);
}

void Settings::VisualizationClassOld::setScalarVariableToFluidVelocityMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
   this->scalar = Settings::visualization::ScalarVariable::fluidVelocityMagnitude;
   emit valueRangeChanged(Settings::simulation().fluidVelocityMagnitudeMinimum,
                          Settings::simulation().fluidVelocityMagnitudeMaximum);
}

void Settings::VisualizationClassOld::setScalarVariableToForceFieldMagnitude()
{
   this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
   this->scalar = Settings::visualization::ScalarVariable::forceFieldMagnitude;
   emit valueRangeChanged(Settings::simulation().forceFieldMagnitudeMinimum,
                          Settings::simulation().forceFieldMagnitudeMaximum);
}

const Settings::VisualizationClassOld& Settings::VisualizationClassOld::instance()
{
   static VisualizationClassOld instance;

   return instance;
}

void Settings::VisualizationClassOld::onTextureVariableChanged(Settings::visualization::ScalarVariable scalarVariable)
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

Settings::visualization::ColorMap Smoke::getColorMap() const
{
    return colorMap;
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent)
{}

Settings::visualization::ColorMap Glyphs::getColorMap() const
{
    return colorMap;
}

Settings::visualization::ColorMap Glyphs::getColorMap() const
{
    return colorMap;
}

void Glyphs::setColorMap(const Settings::visualization::ColorMap &value)
{
    colorMap = value;
}

Settings::visualization::ColorMap::ColorMap(QObject *parent) :
    QObject(parent),
    scalar(visualization::ScalarVariable::fluidDensity)
{}

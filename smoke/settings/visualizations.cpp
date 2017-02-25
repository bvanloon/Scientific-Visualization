#include "visualizations.h"
#include <QDebug>
#include "settings/simulations.h"

Settings::Visualization::Visualization(QObject *parent):
    QObject(parent),
    textureGetter(&::Simulation::getTexCoordFluidDensity),
    vectorScale(1000)
{

}

void Settings::Visualization::setScalarVariableToFluidDensity()
{
    this->textureGetter = &::Simulation::getTexCoordFluidDensity;
    emit valueRangeChanged(0.0f, Settings::simulation().force);
}

void Settings::Visualization::setScalarVariableToFluidVelocityMagnitude()
{
    this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
    emit valueRangeChanged(0.0f, 0.1f);
}

void Settings::Visualization::setScalarVariableToForceFieldMagnitude()
{
    this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
    emit valueRangeChanged(0.0f, 1.0f);
}

const Settings::Visualization &Settings::Visualization::instance()
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
    switch (scalarVariable) {
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

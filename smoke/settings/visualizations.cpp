#include "visualizations.h"
#include <QDebug>

Settings::Visualization::Visualization(QObject *parent):
    QObject(parent),
    textureGetter(&::Simulation::getTexCoordFluidDensity),
    vectorScale(1000)
{

}

void Settings::Visualization::setTextureGetter(Settings::Visualization::ScalarVariable scalar)
{
    switch (scalar) {
    case fluidDensity:
        this->textureGetter = &::Simulation::getTexCoordFluidDensity;
        break;
    case fluidVelocity:
        this->textureGetter = &::Simulation::getTexCoordFluidVelocityMagnitude;
        break;
    case forceFieldMagnitude:
        this->textureGetter = &::Simulation::getTexCoordForceFieldMagnitude;
        break;
    default:
        qDebug() << "Invalid scalar variable, going with the default: fluidDensity.";
        this->textureGetter = &::Simulation::getTexCoordFluidDensity;
        break;
    }
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
    qDebug() << "Settings::Visualization::onScalarVariableChanged";
    setTextureGetter(scalarVariable);
}

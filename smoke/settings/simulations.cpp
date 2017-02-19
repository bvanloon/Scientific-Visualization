#include "simulations.h"
#include "settings/canvass.h"
#include "fftw.h"
#include <QDebug>

settingsns::Simulation::Simulation(QObject *parent):
    QObject(parent),
    dimension(50),
    frozen(false),
    force(10.0f),
    cellSize(-1, -1)
{}

const settingsns::Simulation &settingsns::Simulation::instance()
{
    static Simulation instance;
    return instance;
}

void settingsns::Simulation::onDimensionChanged(int newDimension)
{
    this->dimension = newDimension;
    updateGridCellSize();
}

void settingsns::Simulation::onForceChanged(float newForce)
{
    this->force = newForce;
    emit rangeChanged(0.0, newForce);
}

void settingsns::Simulation::onWindowResized(int width, int height)
{
    updateGridCellSize(width, height);
}

void settingsns::Simulation::updateGridCellSize()
{
    updateGridCellSize(settingsns::canvas().size.width(), settingsns::canvas().size.height());
}

void settingsns::Simulation::updateGridCellSize(int width, int height)
{
    cellSize.setHeight((fftw_real) width / (fftw_real)(dimension + 1));
    cellSize.setWidth((fftw_real) height / (fftw_real)(dimension + 1));
}

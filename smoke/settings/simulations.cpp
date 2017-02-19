#include "simulations.h"
#include "settings/canvass.h"
#include <QDebug>

settingsns::Simulation::Simulation(QObject *parent):
    QObject(parent),
    dimension(50),
    frozen(false),
    force(10.0f)
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
    qDebug() << "TODO: settingsns::Simulation::updateGridCellSize(int width, int height)";
    //    this->grid->cellHeight = (fftw_real) this->canvas->height / (fftw_real)(dimension + 1);
        //    this->grid->cellWidth = (fftw_real) this->canvas->width / (fftw_real)(dimension + 1);
}

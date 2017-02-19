#include "simulations.h"
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

void settingsns::Simulation::updateGridCellSize()
{
    qDebug() << "settingsns::Simulation::updateGridCellSize";
//    this->grid->cellHeight = (fftw_real) this->canvas->height / (fftw_real)(settingsns::simulation().dimension + 1);
//    this->grid->cellWidth = (fftw_real) this->canvas->width / (fftw_real)(settingsns::simulation().dimension + 1);
}

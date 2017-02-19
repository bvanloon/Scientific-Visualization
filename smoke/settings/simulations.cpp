#include "simulations.h"
#include <QDebug>

const settingsns::Simulation &settingsns::Simulation::instance()
{
    static Simulation instance;
    return instance;
}

void settingsns::Simulation::onDimensionChanged(int newDimension)
{
    qDebug() << "settingsns::Simulation::onDimensionChanged";
    this->dimension = newDimension;
    updateGridCellSize();
}

settingsns::Simulation::Simulation(QObject *parent):
    QObject(parent),
    dimension(50),
    frozen(false)
{}

void settingsns::Simulation::updateGridCellSize()
{
    qDebug() << "settingsns::Simulation::updateGridCellSize";
//    this->grid->cellHeight = (fftw_real) this->canvas->height / (fftw_real)(settingsns::simulation().dimension + 1);
//    this->grid->cellWidth = (fftw_real) this->canvas->width / (fftw_real)(settingsns::simulation().dimension + 1);
}

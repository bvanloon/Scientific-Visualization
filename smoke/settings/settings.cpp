#include "settings.h"
#include <QDebug>

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->canvas = new Canvas();
    this->simulation = new Simulation();
    this->grid  = new Grid();
}

Settings::~Settings()
{
    delete canvas;
    delete simulation;
    delete grid;
}


void Settings::onWindowResized(int width, int height)
{
    this->canvas->width = width;
    this->canvas->height = height;

    this->updateGridCellSize();
}

void Settings::onDimensionChanged(int newDimension)
{
    this->simulation->dimension = newDimension;
    this->updateGridCellSize();
}

void Settings::updateGridCellSize()
{
    this->grid->cell_height = (fftw_real) this->canvas->height / (fftw_real)(this->simulation->dimension + 1);
    this->grid->cell_width = (fftw_real) this->canvas->width / (fftw_real)(this->simulation->dimension + 1);
}

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
}

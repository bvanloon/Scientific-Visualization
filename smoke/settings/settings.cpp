#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->canvas = new Canvas();
    this->simulation = new Simulation();
}

Settings::~Settings()
{
    delete canvas;
    delete simulation;
}


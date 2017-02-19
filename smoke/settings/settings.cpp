#include "settings.h"
#include "settingsns.h"
#include "settings/simulations.h"
#include <QDebug>

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->canvas = new Canvas();
    this->visualization = new Visualization();
}

Settings::~Settings()
{
    delete canvas;
    delete visualization;
}

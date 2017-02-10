#include "settings.h"
#include <QDebug>

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

void Settings::onWindowResized(int width, int height)
{
    qDebug() << "settings received: " << width << " " << height;
}


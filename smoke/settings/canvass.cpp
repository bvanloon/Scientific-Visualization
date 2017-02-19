#include "canvass.h"
#include <QDebug>

Settings::Canvas::Canvas(QObject *parent) :
    QObject(parent),
    size(500, 500)
{}


const Settings::Canvas &Settings::Canvas::instance()
{
    static Canvas instance;
    return instance;
}

void Settings::Canvas::onWindowResized(int width, int height)
{
    size.setWidth(width);
    size.setHeight(height);
}

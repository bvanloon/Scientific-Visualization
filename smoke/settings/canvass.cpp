#include "canvass.h"
#include <QDebug>

settingsns::Canvas::Canvas(QObject *parent) :
    QObject(parent),
    size(500, 500)
{}


const settingsns::Canvas &settingsns::Canvas::instance()
{
    static Canvas instance;
    return instance;
}

void settingsns::Canvas::onWindowResized(int width, int height)
{
    size.setWidth(width);
    size.setHeight(height);
}

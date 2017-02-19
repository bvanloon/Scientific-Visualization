#include "canvass.h"

settingsns::Canvas::Canvas(QObject *parent) :
    QObject(parent)
{}


const settingsns::Canvas &settingsns::Canvas::instance()
{
    static Canvas instance;
    return instance;
}

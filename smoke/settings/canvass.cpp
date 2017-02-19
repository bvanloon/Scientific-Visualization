#include "canvass.h"

settingsns::Canvas::Canvas(QObject *parent) :
    QObject(parent),
    size(500, 500)
{}


const settingsns::Canvas &settingsns::Canvas::instance()
{
    static Canvas instance;
    return instance;
}

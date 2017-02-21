#include "visualizations.h"
#include <QDebug>

Settings::Visualization::Visualization(QObject *parent):
    QObject(parent),
    vectorScale(1000)
{}

const Settings::Visualization &Settings::Visualization::instance()
{
    static Visualization instance;
    return instance;
}

#include "visualizations.h"
#include <QDebug>

settingsns::Visualization::Visualization(QObject *parent):
    QObject(parent),
    vectorScale(1000)
{}

const settingsns::Visualization &settingsns::Visualization::instance()
{
    static Visualization instance;
    return instance;
}

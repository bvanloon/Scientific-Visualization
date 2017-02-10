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

QDebug Settings::operator<<(QDebug stream, const Settings &settings)
{
    stream << "Settings [\n\t"
           << settings.canvas
           << "\n\t"
           << settings.simulation
           << "]" << &endl;

    return stream;
}


QDebug Settings::Simulation::operator<<(QDebug stream, const Settings::Simulation &simulation)
{
    stream << "Simulation [\n\t"
           << "dimension: " << simulation.dimension
           << "]" << &endl;

    return stream;
}

QDebug Settings::Canvas::operator<<(QDebug stream, const Settings::Canvas &canvas)
{
    stream << "Canvas [\n\t"
           << "width: " << canvas.width
           << "height: " << canvas.height
           << "]" << &endl;

    return stream;
}

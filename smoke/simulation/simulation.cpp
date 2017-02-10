#include "simulation.h"
#include <QDebug>

Simulation::Simulation(Settings* settings, QObject *parent) :
    QObject(parent), lastMousePosition(0.0f, 0.0f)
{
    this->settings = settings;
    this->realization = new SimulationRealization(settings->simulation->dimension);

    vertices.append(QVector3D(800.0f, 400.0f, 0.0f));
    vertices.append(QVector3D(500.0f, 200.0, 0.0f));
    vertices.append(QVector3D(100.0f, 400.0f, 0.0f));

    colors.append(QVector3D(1.0f, 0.0f, 0.0f));
    colors.append(QVector3D(0.0f, 1.0f, 0.0f));
    colors.append(QVector3D(0.0f, 0.0f, 1.0f));
}

Simulation::~Simulation()
{
    delete this->realization;
}

QVector<QVector3D> Simulation::getVertices()
{
    return this->vertices;
}

QVector<QVector3D> Simulation::getColors()
{
    return this->colors;
}


void Simulation::onMouseMoved(QPoint newPosition)
{
    int xi,yi;

    // Compute the array index that corresponds to the cursor location
    xi = (int)realization->clamp((double)(this->settings->simulation->dimension + 1) * ((double) newPosition.x()/ (double)this->settings->canvas->width));
    yi = (int)realization->clamp((double)(this->settings->simulation->dimension + 1) * ((double)(this->settings->canvas->height - newPosition.y()) / (double)this->settings->canvas->height));

    if (xi > (this->settings->simulation->dimension - 1))  xi = this->settings->simulation->dimension - 1; if (yi > (this->settings->simulation->dimension - 1))  yi = this->settings->simulation->dimension - 1;
    if (xi < 0) xi = 0; if (yi < 0) yi = 0;

    this->vertices.clear();

    vertices.append(QVector3D(newPosition.x(),      402 - newPosition.y(),      0.0f));
    vertices.append(QVector3D(newPosition.x() - 10, 402 - newPosition.y() - 10, 0.0f));
    vertices.append(QVector3D(newPosition.x() + 10, 402 - newPosition.y() - 10, 0.0f));


    this->lastMousePosition = newPosition;
    emit simulationUpdated();
}


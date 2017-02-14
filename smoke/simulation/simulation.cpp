#include "simulation.h"
#include <QDebug>

Simulation::Simulation(Settings* settings, QObject *parent) :
    QObject(parent), lastMousePosition(0.0f, 0.0f)
{
    this->settings = settings;
    this->realization = new SimulationRealization(settings);

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
    //Invert y-position
    newPosition.setY(this->settings->canvas->height - newPosition.y());

    this->realization->addForceAt(newPosition, this->lastMousePosition);
    this->lastMousePosition = newPosition;

    this->vertices.clear();

    vertices.append(QVector3D(newPosition.x(),       newPosition.y(),      0.0f));
    vertices.append(QVector3D(newPosition.x() - 10,  newPosition.y() - 10, 0.0f));
    vertices.append(QVector3D(newPosition.x() + 10,  newPosition.y() - 10, 0.0f));

    emit simulationUpdated();
}


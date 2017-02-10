#include "simulation.h"
#include <QDebug>

Simulation::Simulation(QObject *parent) : QObject(parent)
{
    vertices.append(QVector3D(800.0f, 400.0f, 0.0f));
    vertices.append(QVector3D(500.0f, 200.0, 0.0f));
    vertices.append(QVector3D(100.0f, 400.0f, 0.0f));

    colors.append(QVector3D(1.0f, 0.0f, 0.0f));
    colors.append(QVector3D(0.0f, 1.0f, 0.0f));
    colors.append(QVector3D(0.0f, 0.0f, 1.0f));
}

QVector<QVector3D> Simulation::getVertices()
{
    return this->vertices;
}

QVector<QVector3D> Simulation::getColors()
{
    return this->colors;
}

void Simulation::onMouseMoved(QPointF newPosition)
{
    this->vertices.clear();

    vertices.append(QVector3D(newPosition.x(),      402 - newPosition.y(),      0.0f));
    vertices.append(QVector3D(newPosition.x() - 10, 402 - newPosition.y() - 10, 0.0f));
    vertices.append(QVector3D(newPosition.x() + 10, 402 - newPosition.y() - 10, 0.0f));

    emit simulationUpdated();
}


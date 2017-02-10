#include "simulation.h"

Simulation::Simulation(QObject *parent) : QObject(parent)
{
    vertices.append(QVector3D(-0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.0f, 0.8f, 0.0f));

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


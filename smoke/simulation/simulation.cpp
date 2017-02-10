#include "simulation.h"

Simulation::Simulation():
{
    vertices.append(QVector3D(-0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.0f, 0.8f, 0.0f));

    colors.append(QVector3D(1.0f, 0.0f, 0.0f));
    colors.append(QVector3D(0.0f, 1.0f, 0.0f));
    colors.append(QVector3D(0.0f, 0.0f, 1.0f));
}


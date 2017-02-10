#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QDebug>

class Simulation
{
public:
    Simulation();

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
};

#endif // SIMULATION_H

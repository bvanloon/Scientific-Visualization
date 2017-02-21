#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QPoint>
#include <float.h>

#include "simulation/simulationrealization.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    ~Simulation();

    QVector<QVector3D> getGridVertices();
    QVector<QVector3D> getGridTriangulation();
    QVector<float> getTextureCoordinates();

    SimulationRealization *realization;

    void step();

signals:

public slots:
    void onMouseMoved(QPoint newPosition);

private:
    QPoint lastMousePosition;

};

#endif // SMOKE_H

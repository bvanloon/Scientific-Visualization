#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QPoint>

#include "simulation/simulationrealization.h"
#include "settings/settings.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(Settings *settings, QObject *parent = 0);
    ~Simulation();

    QVector<QVector3D> getVertices();
    QVector<QVector3D> getColors();
    QVector<QVector3D> getGridVertices();
    QVector<QVector3D> getGridTriangulation();
    QVector<float> getTextureCoordinates();

    SimulationRealization *realization;

    void step();

signals:
    void simulationUpdated();

public slots:
    void onMouseMoved(QPoint newPosition);

private:
    QVector<QVector3D> gridVertices;
    QVector<QVector3D> colors;
    Settings *settings;

    QPoint lastMousePosition;
};

#endif // SMOKE_H

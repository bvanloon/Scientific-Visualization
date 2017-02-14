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

signals:
    void simulationUpdated();

public slots:
    void onMouseMoved(QPoint newPosition);

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;

    SimulationRealization *realization;
    Settings *settings;

    QPoint lastMousePosition;
};

#endif // SMOKE_H

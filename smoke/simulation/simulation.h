#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QPoint>
#include <float.h>
#include "grid/uniformgrid.h"

#include "simulation/simulationrealization.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    ~Simulation();

    typedef QVector<float> (Simulation::*textureCoordinateGetter)(void);
    typedef float (Simulation::*textureCoordinateGetterSimple)(int, int);

    QVector<QVector3D> getGridVertices();
    QVector<QVector3D> getGridTriangulation();

    QVector<float> getTexCoordFluidDensity();
    QVector<float> getTexCoordFluidVelocityMagnitude();
    QVector<float> getTexCoordForceFieldMagnitude();

    SimulationRealization *realization;

    void step();

signals:

public slots:
    void onMouseMoved(QPoint newPosition);
    void onStep();

private:
    QPoint lastMousePosition;
    UniformGrid* grid;

    QVector<float> getTexCoord(textureCoordinateGetterSimple getter);

    int to1DIndex(int i, int j);

    float getFluidDensityAt(int i, int j);
    float getFluidDensityAt(int idx);

    QVector2D getFluidVelocityAt(int i, int j);
    QVector2D getFluidVelocityAt(int idx);

    float getFluidVelocityMagnitudeAt(int i, int j);
    float getFluidVelocityMagnitudeAt(int idx);

    QVector2D getForceAt(int i, int j);
    QVector2D getForceAt(int idx);

    float getForceMagnitudeAt(int i, int j);
    float getForceMagnitudeAt(int idx);
};

#endif // SMOKE_H

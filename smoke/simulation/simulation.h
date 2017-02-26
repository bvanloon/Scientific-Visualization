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

    typedef QVector<float> (Simulation::*textureCoordinateGetter)(QVector<QVector3D>);
    typedef float (Simulation::*textureCoordinateGetterSimple)(int, int);

    QVector<QVector3D> getGridVertices();
    QVector<QVector3D> getGridTriangulation();

    QVector<float> getTexCoordFluidDensity(QVector<QVector3D> vertexPositions);
    QVector<float> getTexCoordFluidVelocityMagnitude(QVector<QVector3D> vertexPositions);
    QVector<float> getTexCoordForceFieldMagnitude(QVector<QVector3D> vertexPositions);

    SimulationRealization *realization;

    void step();

signals:

public slots:
    void onMouseMoved(QPoint newPosition);
    void onStep();
    void onWindowResized(int width, int height);

private:
    QPoint lastMousePosition;
    UniformGrid* grid;

    QVector<float> getTexCoord(textureCoordinateGetterSimple getter, QVector<QVector3D> vertexPositions);

    int to1DIndex(int i, int j);
    int to1DIndex(QVector3D position);

    float getFluidDensityAt(int i, int j);
    float getFluidDensityAt(int idx);
    float getFluidDensityAt(QVector3D position);

    QVector2D getFluidVelocityAt(int i, int j);
    QVector2D getFluidVelocityAt(int idx);
    QVector2D getFluidVelocityAt(QVector3D position);

    float getFluidVelocityMagnitudeAt(int i, int j);
    float getFluidVelocityMagnitudeAt(int idx);
    float getFluidVelocityMagnitudeAt(QVector3D position);

    QVector2D getForceAt(int i, int j);
    QVector2D getForceAt(int idx);
    QVector2D getForceAt(QVector3D position);

    float getForceMagnitudeAt(int i, int j);
    float getForceMagnitudeAt(int idx);
    float getForceMagnitudeAt(QVector3D position);
};

#endif // SMOKE_H

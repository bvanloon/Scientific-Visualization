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
#include "grid/triangulation.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    ~Simulation();

    typedef QVector<float> (Simulation::*textureCoordinateGetter)(Triangulation);

    QVector<QVector3D> getSimpleHedgeHodges();
    Triangulation getGridTriangulation();

    QVector<float> getTexCoordFluidDensity(Triangulation triangulation);
    QVector<float> getTexCoordFluidVelocityMagnitude(Triangulation triangulation);
    QVector<float> getTexCoordForceFieldMagnitude(Triangulation triangulation);

    SimulationRealization *realization;

    void step();

signals:

public slots:
    void onMouseMoved(QPoint newPosition);
    void onStep();
    void onWindowResized(int width, int height);

private:
    QPoint lastMousePosition;
    UniformGrid* simulationGrid;
    UniformGrid* visualizationGrid;

    typedef float (Vertex::*textureCoordinateGetterSimple)() const;
    QVector<float> getTexCoord(textureCoordinateGetterSimple getter, Triangulation triangulation);
};

#endif // SMOKE_H

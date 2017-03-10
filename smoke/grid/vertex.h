#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>
#include <QDebug>
#include "settings/simulationsettings.h"

class Cell;

class Vertex
{
public:
    Vertex(const QVector3D *position = NULL);
    virtual ~Vertex();

    typedef float (Vertex::*scalarGetter)() const;
    typedef QVector2D (Vertex::*vectorGetter)() const;

    const QVector3D* getPosition() const;

    friend QDebug operator<<(QDebug stream, const Vertex &vertex);
    friend QDebug operator<<(QDebug stream, Vertex *vertex);

    virtual QVector2D getFluidVelocity() const = 0;
    virtual float getFluidVelocityMagnitude() const = 0;

    virtual QVector2D getForce() const = 0;
    virtual float getForceMagnitude() const = 0;

    virtual float getFluidDensity() const = 0;

    static Vertex::scalarGetter getScalarGetter(Settings::sim::Scalar scalar);

protected:
    const QVector3D *position;

};

class StructuredGridVertex: public Vertex{
public:
    virtual QVector2D getFluidVelocity() const = 0;
    virtual float getFluidVelocityMagnitude() const = 0;

    virtual QVector2D getForce() const = 0;
    virtual float getForceMagnitude() const = 0;

    virtual float getFluidDensity() const = 0;

    Cell *getLowerRightCell() const;
    void setLowerRightCell(Cell *value);
    bool hasLowerRightCell();

protected:
    StructuredGridVertex(const QVector3D *position);

    Cell *lowerRightCell;
};

class SimulationVertex: public StructuredGridVertex
{
public:

    SimulationVertex(const QVector3D *position, double *vx, double *vy, double *fx, double *fy, double *rho);

    friend QDebug operator<<(QDebug stream, const SimulationVertex &vertex);
    friend QDebug operator<<(QDebug stream, SimulationVertex *vertex);

    virtual QVector2D getFluidVelocity() const;
    virtual float getFluidVelocityMagnitude() const;

    virtual QVector2D getForce() const;
    virtual float getForceMagnitude() const;

    virtual float getFluidDensity() const;

private:
    double *vx, *vy;
    double *fx, *fy;
    double *rho;

};

class VisualizationVertex: public StructuredGridVertex
{
public:
    VisualizationVertex(const QVector3D *position, Cell* containingCell);

    friend QDebug operator<<(QDebug stream, const VisualizationVertex &vertex);
    friend QDebug operator<<(QDebug stream, VisualizationVertex *vertex);

    virtual QVector2D getFluidVelocity() const;
    virtual float getFluidVelocityMagnitude() const;

    virtual QVector2D getForce() const;
    virtual float getForceMagnitude() const;

    virtual float getFluidDensity() const;

private:
    Cell* containingCell;
};


#endif // VERTEX_H

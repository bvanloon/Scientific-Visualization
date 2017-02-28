#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>
#include <QDebug>

class Cell;
class Vertex
{
public:
    Vertex(const QVector3D *position = NULL);
    virtual ~Vertex();

    const QVector3D* getPosition() const;

    friend QDebug operator<<(QDebug stream, const Vertex &vertex);
    friend QDebug operator<<(QDebug stream, Vertex *vertex);

    virtual QVector2D getFluidVelocity() const = 0;

    virtual float getFluidVelocityMagnitude() const = 0;

protected:
    const QVector3D *position;

};

class SimulationVertex: public Vertex
{
public:
    SimulationVertex(const QVector3D *position, double *vx, double *vy);

    friend QDebug operator<<(QDebug stream, const SimulationVertex &vertex);
    friend QDebug operator<<(QDebug stream, SimulationVertex *vertex);

    virtual QVector2D getFluidVelocity() const;
    virtual float getFluidVelocityMagnitude() const;

private:
    double* vx;
    double* vy;
};

class VisualizationVertex: public Vertex
{
public:
    VisualizationVertex(const QVector3D *position, Cell* cell);

    friend QDebug operator<<(QDebug stream, const VisualizationVertex &vertex);
    friend QDebug operator<<(QDebug stream, VisualizationVertex *vertex);

private:
    Cell* cell;
};


#endif // VERTEX_H

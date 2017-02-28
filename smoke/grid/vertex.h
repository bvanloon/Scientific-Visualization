#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QDebug>

class Vertex
{
public:
    Vertex(const QVector3D *position = NULL);

    const QVector3D* getPosition() const;

    friend QDebug operator<<(QDebug stream, const Vertex &vertex);
    friend QDebug operator<<(QDebug stream, Vertex *vertex);

private:
    const QVector3D *position;

};

class SimulationVertex : public Vertex
{
public:
    QVector2D getFluidVelocity();

private:
    double* vx;
    double* vy;
};

#endif // VERTEX_H

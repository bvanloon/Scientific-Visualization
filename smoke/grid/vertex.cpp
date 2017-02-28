#include "vertex.h"

Vertex::Vertex(const QVector3D *position):
    position(position)
{}

Vertex::~Vertex()
{

}

const QVector3D *Vertex::getPosition() const
{
    return this->position;
}

QDebug operator<<(QDebug stream, const Vertex &vertex)
{
    stream << "Vertex ["
           << " position: "    << *vertex.position
           << "]";
    return stream;
}


QDebug operator<<(QDebug stream, Vertex *vertex)
{
    stream << *vertex;
    return stream;
}

SimulationVertex::SimulationVertex(const QVector3D *position, double *vx, double *vy):
    Vertex(position)
{
    this->vx = vx;
    this->vy = vy;
}

QVector2D SimulationVertex::getFluidVelocity() const
{
    return QVector2D(*(vx), *(vy));
}

QDebug operator<<(QDebug stream, const SimulationVertex &vertex)
{
    stream << "SimulationVertex ["
           << " position: "    << *vertex.position
           << " (vx, vy): (" << *vertex.vx << ", " << *vertex.vy << ")"
           << "]";
    return stream;
}

QDebug operator<<(QDebug stream, SimulationVertex *vertex)
{
    stream << *vertex;
    return stream;
}

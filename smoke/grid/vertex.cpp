#include "vertex.h"
#include "cell.h"

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
    StructuredGridVertex(position)
{
    this->vx = vx;
    this->vy = vy;
}

QVector2D SimulationVertex::getFluidVelocity() const
{
    return QVector2D(*(vx), *(vy));
}

float SimulationVertex::getFluidVelocityMagnitude() const
{
    return getFluidVelocity().length();
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

QDebug operator<<(QDebug stream, const VisualizationVertex &vertex)
{
    stream << "VisualizationVertex ["
           << " position: " << *vertex.position
           << "]";
    return stream;
}

QDebug operator<<(QDebug stream, VisualizationVertex *vertex)
{
    stream << *vertex;
    return stream;
}

VisualizationVertex::VisualizationVertex(const QVector3D *position, Cell *cell):
    Vertex(position),
    cell(cell)
{}

QVector2D VisualizationVertex::getFluidVelocity() const
{
    qDebug() << "VisualizationVertex::getFluidVelocity(): not yet implemented";
}

float VisualizationVertex::getFluidVelocityMagnitude() const
{
    qDebug() << "VisualizationVertex::getFluidVelocityMagnitude(): not yet implemented";
}

StructuredGridVertex::StructuredGridVertex(const QVector3D *position):
    Vertex(position)
{}

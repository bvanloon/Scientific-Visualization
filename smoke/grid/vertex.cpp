#include "vertex.h"

Vertex::Vertex(const QVector3D *position):
    position(position)
{}

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

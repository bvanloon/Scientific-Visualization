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

#endif // VERTEX_H

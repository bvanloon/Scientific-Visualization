#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    Vertex(QVector3D* position = NULL);

private:

    QVector3D *position;

};

#endif // VERTEX_H

#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include "abstractengine.h"
#include "simulation/simulation.h"

class VectorEngine : AbstractEngine
{
public:
    VectorEngine();
    virtual ~VectorEngine();

    void draw(Simulation* simulation);

private:
    void initBuffers();

    int updateBuffers(Simulation* simulation);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
};

#endif // VECTORENGINE_H

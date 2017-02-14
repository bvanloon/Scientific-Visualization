#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "simulation/simulation.h"

class VectorEngine : protected QOpenGLFunctions
{
public:
    VectorEngine();
    virtual ~VectorEngine();

    void draw(Simulation* simulation);

private:
    void initBuffers();

    void updateBuffers(Simulation* simulation);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
};

#endif // VECTORENGINE_H

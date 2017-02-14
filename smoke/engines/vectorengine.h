#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "simulation/simulation.h"
#include "settings/settings.h"

class VectorEngine : protected QOpenGLFunctions
{
public:
    VectorEngine(Settings* settings);
    virtual ~VectorEngine();

    void draw(Simulation* simulation);

private:
    void initBuffers();

    void updateBuffers(Simulation* simulation);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

    Settings* settings;

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
};

#endif // VECTORENGINE_H

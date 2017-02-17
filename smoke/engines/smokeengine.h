#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "simulation/simulation.h"

class SmokeEngine : protected QOpenGLFunctions
{
public:
    SmokeEngine(Settings* settings);
    virtual ~SmokeEngine();

    void draw(Simulation* simulation);

private:
    Settings* settings;
    void initBuffers();

    int updateBuffers(Simulation* simulation);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
    QOpenGLBuffer* textureCoordinateBuffer;
};


#endif // SMOKEENGINE_H

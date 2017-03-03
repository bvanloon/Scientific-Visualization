#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"
#include "grid/triangulation.h"

class SmokeEngine : protected QOpenGLFunctions
{
public:
    SmokeEngine();
    virtual ~SmokeEngine();

    void draw(Simulation* simulation);

private:
    void initBuffers();

    int updateBuffers(Simulation* simulation);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
    QOpenGLBuffer* textureCoordinateBuffer;
};


#endif // SMOKEENGINE_H

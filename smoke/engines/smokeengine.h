#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"

#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"

class SmokeEngine : AbstractEngine
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

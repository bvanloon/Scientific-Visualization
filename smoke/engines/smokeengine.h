#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"

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

    QOpenGLBuffer* textureCoordinateBuffer;
};


#endif // SMOKEENGINE_H

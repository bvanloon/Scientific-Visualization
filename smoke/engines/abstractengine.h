#ifndef ABSTRACTENGINE_H
#define ABSTRACTENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"

class AbstractEngine : protected QOpenGLFunctions
{
public:
    AbstractEngine();
    virtual void draw(Simulation* Simulation) = 0;

protected:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;

     void initBuffers();
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);
};

#endif // ABSTRACTENGINE_H

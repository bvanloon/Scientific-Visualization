#ifndef ABSTRACTENGINE_H
#define ABSTRACTENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class AbstractEngine : QOpenGLFunctions
{
public:
    AbstractEngine();
};

#endif // ABSTRACTENGINE_H

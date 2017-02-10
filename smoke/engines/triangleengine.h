#ifndef TRIANGELENGINE_H
#define TRIANGELENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class TriangleEngine : protected QOpenGLFunctions
{
public:
    TriangleEngine();
    virtual ~TriangleEngine();

    void draw();

private:
    void initBuffers();
    void initTriangleGeometry();

    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
    QOpenGLBuffer* colorBuffer;
};

#endif // TRIANGELENGINE_H

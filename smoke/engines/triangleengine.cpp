#include "triangleengine.h"

TriangleEngine::TriangleEngine()
{
    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

    initBuffers();
    initTriangleGeometry();
}


TriangleEngine::~TriangleEngine()
{
    this->vertexBuffer->destroy();
    this->colorBuffer->destroy();
    this->vao.destroy();
}

void TriangleEngine::draw(Simulation *simulation)
{
    this->vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    this->vao.release();
}

void TriangleEngine::initBuffers()
{
    this->vao.create();
    this->vao.bind();

    this->vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->vertexBuffer->create();
    this->vertexBuffer->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->colorBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->colorBuffer->create();
    this->colorBuffer->bind();

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->vao.release();
}

void TriangleEngine::initTriangleGeometry()
{
    QVector<QVector3D> vertices = QVector<QVector3D>();
    vertices.append(QVector3D(-0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.8f, -0.8f, 0.0f));
    vertices.append(QVector3D(0.0f, 0.8f, 0.0f));

    updateBuffer(this->vertexBuffer, vertices);

    QVector<QVector3D> colors = QVector<QVector3D>();
    colors.append(QVector3D(1.0f, 0.0f, 0.0f));
    colors.append(QVector3D(0.0f, 1.0f, 0.0f));
    colors.append(QVector3D(0.0f, 0.0f, 1.0f));

    updateBuffer(this->colorBuffer, colors);
}

void TriangleEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

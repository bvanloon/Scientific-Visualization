#include "abstractengine.h"

AbstractEngine::AbstractEngine()
{
    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

}

void AbstractEngine::initBuffers()
{
    this->vao.create();
    this->vao.bind();

    this->vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->vertexBuffer->create();
    this->vertexBuffer->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    this->vao.release();
}


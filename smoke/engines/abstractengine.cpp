#include "abstractengine.h"

AbstractEngine::AbstractEngine()
{
    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->textureCoordinateBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

}

AbstractEngine::~AbstractEngine()
{
    this->vertexBuffer->destroy();
    this->textureCoordinateBuffer->destroy();
    this->vao.destroy();
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

    this->textureCoordinateBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->textureCoordinateBuffer->create();
    this->textureCoordinateBuffer->bind();

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

    this->vao.release();
}

void AbstractEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

void AbstractEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<float> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

void AbstractEngine::drawWithMode(Simulation *Simulation, int mode, int bufferLength )
{
    this->vao.bind();
    glDrawArrays(mode, 0, bufferLength);
    this->vao.release();
}


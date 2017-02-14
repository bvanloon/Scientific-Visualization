#include "vectorengine.h"

VectorEngine::VectorEngine(Settings *settings) :
    settings(settings)
{
    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

    initBuffers();
}

VectorEngine::~VectorEngine()
{
    this->vertexBuffer->destroy();
    this->vao.destroy();
}

void VectorEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);
    this->vao.bind();
    glDrawArrays(GL_LINES, 0, bufferLength);
    this->vao.release();
}

void VectorEngine::initBuffers()
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

int VectorEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> vertices = simulation->getGridVertices();
    updateBuffer(this->vertexBuffer, vertices);
    return vertices.length();
}

void VectorEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}


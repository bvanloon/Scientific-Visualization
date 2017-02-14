#include "smokeengine.h"

SmokeEngine::SmokeEngine(Settings *settings):
    settings(settings)
{

    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

    initBuffers();
}

SmokeEngine::~SmokeEngine()
{
    this->vertexBuffer->destroy();
    this->vao.destroy();
}

void SmokeEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);

    this->vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, bufferLength);
    this->vao.release();
}

void SmokeEngine::initBuffers()
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

int SmokeEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> triangles = simulation->getGridTriangulation();

    updateBuffer(this->vertexBuffer, triangles);
    return triangles.length();
}

void SmokeEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

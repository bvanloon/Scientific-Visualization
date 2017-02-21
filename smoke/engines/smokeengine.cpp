#include "smokeengine.h"

SmokeEngine::SmokeEngine()
{

    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->textureCoordinateBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

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


    this->textureCoordinateBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->textureCoordinateBuffer->create();
    this->textureCoordinateBuffer->bind();

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

    this->vao.release();


}

int SmokeEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> triangles = simulation->getGridTriangulation();
    QVector<float> textureCoordinates = simulation->getTextureCoordinates();

    updateBuffer(this->vertexBuffer, triangles);
    updateBuffer(this->textureCoordinateBuffer,textureCoordinates);
    return triangles.length();
}

void SmokeEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

void SmokeEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<float> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

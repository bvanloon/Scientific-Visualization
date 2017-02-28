#include "smokeengine.h"

SmokeEngine::SmokeEngine()
{
    this->textureCoordinateBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

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
    AbstractEngine::initBuffers();
    this->vao.bind();

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

    QVector<float> textureCoordinates = (simulation->*Settings::visualization().textureGetter)(triangles);

    updateBuffer(this->vertexBuffer, triangles);
    updateBuffer(this->textureCoordinateBuffer,textureCoordinates);
    return triangles.length();
}

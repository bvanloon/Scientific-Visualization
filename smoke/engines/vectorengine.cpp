#include "vectorengine.h"

VectorEngine::VectorEngine()
{
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
    AbstractEngine::initBuffers();
}

int VectorEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> vertices = simulation->getGridVertices();
    updateBuffer(this->vertexBuffer, vertices);
    return vertices.length();
}

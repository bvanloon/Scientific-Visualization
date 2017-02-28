#include "vectorengine.h"

VectorEngine::VectorEngine()
{
    initBuffers();
}

void VectorEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);
    drawWithMode(simulation, GL_LINES, bufferLength);
}

void VectorEngine::initBuffers()
{
    AbstractEngine::initBuffers();
}

int VectorEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> vertices = simulation->getSimpleHedgeHodges();
    updateBuffer(this->vertexBuffer, vertices);
    return vertices.length();
}

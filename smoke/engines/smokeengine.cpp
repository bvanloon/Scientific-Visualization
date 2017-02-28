#include "smokeengine.h"

SmokeEngine::SmokeEngine()
{
    initBuffers();
}


void SmokeEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);
    drawWithMode(simulation, GL_TRIANGLES, bufferLength);
}

void SmokeEngine::initBuffers()
{
    AbstractEngine::initBuffers();
}

int SmokeEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> triangles = simulation->getGridTriangulation();
    QVector<float> textureCoordinates = (simulation->*Settings::visualization().textureGetter)(triangles);

    updateBuffer(this->vertexBuffer, triangles);
    updateBuffer(this->textureCoordinateBuffer,textureCoordinates);
    return triangles.length();
}

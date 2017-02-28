#include "smokeengine.h"

SmokeEngine::SmokeEngine() {
}

void SmokeEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);
    drawWithMode(simulation, GL_TRIANGLES, bufferLength);
}


int SmokeEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> triangles = simulation->getGridTriangulation();
    QVector<float> textureCoordinates = (simulation->*Settings::visualization().textureGetter)(triangles);

    updateBuffer(this->vertexBuffer, triangles);
    updateBuffer(this->textureCoordinateBuffer,textureCoordinates);
    return triangles.length();
}



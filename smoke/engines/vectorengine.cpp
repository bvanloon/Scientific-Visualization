#include "vectorengine.h"


VectorEngine::VectorEngine() :
    AbstractEngine() {

}

void VectorEngine::draw(Simulation *simulation)
{
    int bufferLength = this->updateBuffers(simulation);
    drawWithMode(simulation, GL_LINES, bufferLength);
}

int VectorEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> vertices = simulation->getSimpleHedgeHodges();
    updateBuffer(this->vertexBuffer, vertices);
    QVector<float> textureCoordinates = (simulation->*Settings::visualization().textureGetter)(vertices);
    //updateBuffer(this->textureCoordinateBuffer,QVector<float>(vertices.size(), 0.5f));
    updateBuffer(this->textureCoordinateBuffer,textureCoordinates);
    return vertices.length();
}

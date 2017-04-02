#include "smokebuilder.h"

SmokeBuilder::SmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter) :
   grid(grid),
   textureGetter(textureGetter),
   data(GL_TRIANGLES),
   normal(QVector3D(0.0, 0.0, 1.0))
{
   build();
}

GPUData SmokeBuilder::getGPUData() const
{
    return data;
}

void SmokeBuilder::build()
{
    QVector<Vertex *> vertices = grid->getTriangulation().getVertices();
   for (Vertex *vertex : vertices) this->addVertex(vertex);
}

void SmokeBuilder::addVertex(Vertex *vertex)
{
   double textureCoordinate = (vertex->*textureGetter)();
   QVector3D position = *vertex->getPosition();
   data.addElement(position, normal, textureCoordinate);
}

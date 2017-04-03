#include "smokebuilder.h"

SmokeBuilder::SmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter) :
   data(GL_TRIANGLES),
   getTextureCoordinate(textureGetter),
   normal(QVector3D(0.0, 0.0, 1.0)),
   grid(grid)
{}

GPUData SmokeBuilder::getGPUData()
{
   if (data.isEmpty()) build();
   return data;
}

void SmokeBuilder::build()
{
   QVector<Vertex *> vertices = grid->getTriangulation().getVertices();
   for (Vertex *vertex : vertices) addVertex(vertex);
}

void SmokeBuilder::addVertex(Vertex *vertex)
{
   double textureCoordinate = (vertex->*getTextureCoordinate)();
   QVector3D position = *vertex->getPosition();
   data.addElement(position, normal, textureCoordinate);
}

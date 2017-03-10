#include "grid.h"

Grid::Grid(int numberOfVertices, bool hasPadding) :
   vertices(numberOfVertices),
   vertexPositions(numberOfVertices),
   hasPadding(hasPadding)
{}

Grid::~Grid()
{
//    Somehow distinguish between simulation grid and visualizationg rid.
//   for (int i = 0; i < vertices.size(); i++)
//   {
//      delete vertices[i];
//   }
//   for (int i = 0; i < cells.size(); i++)
//   {
//      delete cells[i];
//   }
}

GlyphData Grid::getGlyphData() const
{
   GlyphData data = GlyphData(this->numVertices());

   QVector<Vertex *>::const_iterator currentVertex = vertices.begin();
   QVector3D position;
   QVector2D direction;
   Vertex *vertex;
   float textureCoordinate;

   for ( ; currentVertex != vertices.end(); currentVertex++)
   {
      vertex = (*currentVertex);
      position = *(vertex->getPosition());
      direction = vertex->getFluidVelocity();
      textureCoordinate = vertex->getFluidDensity();
      data.addGlyph(position, direction, textureCoordinate);
   }
   return data;
}

const QVector<QVector3D>& Grid::getVertexPositions() const
{
   return this->vertexPositions;
}

const QVector<Vertex *>& Grid::getVertices() const
{
   return this->vertices;
}

const QVector<Cell *>& Grid::getCells() const
{
   return this->cells;
}

int Grid::numVertices() const
{
   return this->vertexPositions.size();
}

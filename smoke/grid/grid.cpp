#include "grid.h"
#include "settings/visualizationsettings.h"

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
   int numVertices = this->vertexPositions.size();
   return numVertices;
}

QMultiMap<Index2D, Vertex *> Grid::getVertexMap() const
{
   return vertexMap;
}

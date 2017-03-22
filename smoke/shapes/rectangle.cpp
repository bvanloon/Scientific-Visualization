#include "rectangle.h"

shapes::Rectangle::Rectangle(double width, double height) :
   width(width),
   height(height)
{}

shapes::Rectangle::Rectangle(double size) :
   width(size),
   height(size)
{}

mesh::TriangleMesh *shapes::Rectangle::toTriangleMesh()
{
   int numVertices = 4;
   int numFaces = 2;

   mesh::TriangleMesh *mesh = new mesh::TriangleMesh(numVertices, numFaces);

   double xAxisOffset = this->width / 2;
   double yAxisOffset = this->height / 2;

   mesh::Vertex *lowerLeft = mesh->addVertex(QVector3D(-xAxisOffset, -yAxisOffset, 0.0));
   mesh::Vertex *lowerRight = mesh->addVertex(QVector3D(xAxisOffset, -yAxisOffset, 0.0));
   mesh::Vertex *upperLeft = mesh->addVertex(QVector3D(-xAxisOffset, yAxisOffset, 0.0));
   mesh::Vertex *upperRight = mesh->addVertex(QVector3D(xAxisOffset, yAxisOffset, 0.0));

   mesh->addTriangle(lowerLeft, upperLeft, upperRight);
   mesh->addTriangle(lowerLeft, upperRight, lowerRight);

   return mesh;
}

#include "seedcurve.h"

SeedCurve::SeedCurve() :
   shapes::PolyLine()
{}

GPUData SeedCurve::GPUDataEdges(int resolution)
{
   GPUData curveData;
   GPUData edgeData;

   QList<QVector3D>::iterator edgeStart = this->vertices.begin();
   QList<QVector3D>::iterator edgeEnd = edgeStart + 1;

   for ( ; edgeEnd < this->vertices.end(); ++edgeStart, ++edgeEnd)
   {
      edgeData = edgeToGPUData(*edgeStart, *edgeEnd, resolution);
      curveData.extend(edgeData);
   }
   return curveData;
}

GPUData SeedCurve::edgeToGPUData(QVector3D start, QVector3D end, int resolution)
{
   float minTextureCoordinate = 0.0;

   float maxTextureCoordinate = 1.0;

   QVector3D normal = QVector3D(0.0, 0.0, 1.0);

   QVector3D direction = (end - start);

   double stepLength = direction.length() / resolution;

   direction.normalize();

   QVector3D pieceStart = start;
   QVector3D pieceEnd = start + stepLength * direction;

   GPUData data(GL_LINES);

   for (int i = 0; i < resolution; i++)
   {
      data.addElement(pieceStart, normal, minTextureCoordinate);
      data.addElement(pieceEnd, normal, maxTextureCoordinate);

      pieceStart = pieceEnd;
      pieceEnd += stepLength * direction;
   }
   return data;
}

GPUData SeedCurve::GPUDataVertices()
{
   GPUData data(GL_POINTS);
   QVector3D normal = QVector3D(0.0, 0.0, 1.0);
   for (auto vertex : vertices)
   {
      data.addElement(vertex, normal, 1.0);
   }
   return data;
}

void SeedCurve::applyTransformation(QMatrix4x4 transform)
{
   QVector3D currentVertex;
   for (int i = 0; i < vertices.length(); i++)
   {
      currentVertex = vertices.takeFirst();
      vertices.append(currentVertex * transform);
   }
}

void SeedCurve::removeTail()
{
   if (!vertices.isEmpty()) this->vertices.takeLast();
}

QList<QVector3D> SeedCurve::getSeedPoints(int resolution)
{
   QList<QVector3D> seedPoints;
   QList<QVector3D>::iterator start = this->vertices.begin();
   QList<QVector3D>::iterator end = start + 1;

   for ( ; end < this->vertices.end(); ++start, ++end)
   {
      seedPoints.append(edgeToSeedPoints(*start, *end, resolution));
   }
   return seedPoints;
}

QList<QVector3D> SeedCurve::edgeToSeedPoints(QVector3D start, QVector3D end, int resolution)
{
   QVector3D direction = (end - start);
   double stepLength = direction.length() / resolution;
   direction.normalize();

   QVector3D current = start;
   QList<QVector3D> seedPoints;

   for (int i = 0; i < resolution; i++, current += stepLength * direction)
   {
      seedPoints.append(current);
   }
   return seedPoints;
}

#include "seedcurve.h"

SeedCurve::SeedCurve() :
   shapes::PolyLine()
{}

GPUData SeedCurve::toGPUData(int resolution)
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

void SeedCurve::applyTransformation(QMatrix4x4 transform)
{
   QVector3D currentVertex;
   for (int i = 0; i < vertices.length(); i++)
   {
      currentVertex = vertices.takeFirst();
      vertices.append(currentVertex * transform);
   }
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

   data.addElement(start, normal, minTextureCoordinate);
   data.addElement(end, normal, maxTextureCoordinate);


   for (int i = 0; i < resolution; i++)
   {
      data.addElement(pieceStart, normal, minTextureCoordinate);
      data.addElement(pieceEnd, normal, maxTextureCoordinate);

      pieceStart = pieceEnd;
      pieceEnd += stepLength * direction;
   }
   return data;
}

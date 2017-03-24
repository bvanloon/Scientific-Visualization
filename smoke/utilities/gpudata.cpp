#include "gpudata.h"
#include <assert.h>
#include <QDebug>

GPUData::GPUData()
{}

void GPUData::extend(GPUData data)
{
   this->vertices.append(data.getVertices());
   this->normals.append(data.getNormals());
   this->textureCoordinates.append(data.getTextureCoordinates());
}

int GPUData::numElements()
{
   return this->vertices.length();
}

void GPUData::addElement(QVector3D vertex, QVector3D normal, float textureCoordinate)
{
   this->vertices.append(vertex);
   this->normals.append(normal);
   this->textureCoordinates.append(textureCoordinate);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector3D normal, float textureCoordinate)
{
   QVector<QVector3D> normals = QVector<QVector3D>(vertices.size(), normal);
   QVector<float> textureCoordinates = QVector<float>(vertices.size(), textureCoordinate);
   addElements(vertices, normals, textureCoordinates);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, float textureCoordinate)
{
   QVector<float> textureCoordinates = QVector<float>(vertices.size(), textureCoordinate);
   addElements(vertices, normals, textureCoordinates);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates)
{
   assert(this->vertices.length() == this->normals.length());
   assert(this->normals.length() == this->textureCoordinates.length());

   this->vertices.append(vertices);
   this->normals.append(normals);
   this->textureCoordinates.append(textureCoordinates);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector3D normal, QVector<float> textureCoordinates)
{
   QVector<QVector3D> normals = QVector<QVector3D>(vertices.size(), normal);
   addElements(vertices, normals, textureCoordinates);
}

QVector<QVector3D> GPUData::getVertices() const
{
   return this->vertices;
}

QVector<float> GPUData::getTextureCoordinates() const
{
   return this->textureCoordinates;
}

QVector<QVector3D> GPUData::getNormals() const
{
   return this->normals;
}

GPUData GPUData::cube()
{
   GPUData data;
   QVector3D normal;

   float negative = 100;
   float positive = 400;

   float negativeZ = -1.0;
   float positiveZ = 1.0;

   //Forward facing
   normal = QVector3D(0, 0, 1);
   //Lower Left Triangle
   data.addElement(QVector3D(negative, negative, negativeZ), normal, 1.0);
   data.addElement(QVector3D(negative, positive, negativeZ), normal, 2.0);
   data.addElement(QVector3D(positive, negative, negativeZ), normal, 4.0);

   //Upper Right Triangle
   data.addElement(QVector3D(negative, positive, negativeZ), normal, 2.0);
   data.addElement(QVector3D(positive, negative, negativeZ), normal, 4.0);
   data.addElement(QVector3D(positive, positive, negativeZ), normal, 3.0);

   //Left facing
   normal = QVector3D(-1, 0, 0);
   //Lower Left Triangle
   data.addElement(QVector3D(negative, positive, negativeZ), normal, 2.0);
   data.addElement(QVector3D(negative, negative, negativeZ), normal, 1.0);
   data.addElement(QVector3D(negative, negative, positiveZ), normal, 5.0);

   //Upper Right Triangle
   data.addElement(QVector3D(negative, positive, negativeZ), normal, 2.0);
   data.addElement(QVector3D(negative, positive, positiveZ), normal, 6.0);
   data.addElement(QVector3D(negative, negative, positiveZ), normal, 5.0);

   return data;
}

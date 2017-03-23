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

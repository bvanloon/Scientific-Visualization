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

   float yA = 100;
   float yB = 200;
   float yC = 300;
   float yD = 400;
   float yE = 500;

   float negx = 200;
   float midx = 300;
   float posx = 400;

   float negz = -100.0;
   float midz = 0.0;
   float posz = 100.0;

   QVector3D A = QVector3D(midx, yE, negz);
   QVector3D B = QVector3D(midx, yC, negz);
   QVector3D C = QVector3D(negx, yB, midz);
   QVector3D D = QVector3D(negx, yD, midz);
   QVector3D E = QVector3D(posx, yD, midz);
   QVector3D F = QVector3D(posx, yB, midz);
   QVector3D G = QVector3D(midx, yC, posz);
   QVector3D H = QVector3D(midx, yA, posz);

   //Forward facing
   normal = QVector3D::crossProduct(A, C);
   //left back Triangle
   data.addElement(A, normal, 1.0);
   data.addElement(C, normal, 1.0);
   data.addElement(B, normal, 1.0);

   data.addElement(A, normal, 1.0);
   data.addElement(D, normal, 1.0);
   data.addElement(C, normal, 1.0);


   normal = QVector3D::crossProduct(A, E);
   //right back
   data.addElement(A, normal, 1.0);
   data.addElement(B, normal, 1.0);
   data.addElement(E, normal, 1.0);

   data.addElement(B, normal, 1.0);
   data.addElement(F, normal, 1.0);
   data.addElement(E, normal, 1.0);

   normal = QVector3D::crossProduct(C, H);
   //Bottom
   data.addElement(B, normal, 1.0);
   data.addElement(C, normal, 1.0);
   data.addElement(H, normal, 1.0);

   data.addElement(B, normal, 1.0);
   data.addElement(H, normal, 1.0);
   data.addElement(F, normal, 1.0);

   normal = QVector3D::crossProduct(A, G);
   //Top
   data.addElement(A, normal, 1.0);
   data.addElement(D, normal, 1.0);
   data.addElement(G, normal, 1.0);

   data.addElement(A, normal, 1.0);
   data.addElement(G, normal, 1.0);
   data.addElement(E, normal, 1.0);

   normal = QVector3D::crossProduct(D, G);
   //Left front
   data.addElement(C, normal, 1.0);
   data.addElement(G, normal, 1.0);
   data.addElement(D, normal, 1.0);

   data.addElement(C, normal, 1.0);
   data.addElement(H, normal, 1.0);
   data.addElement(G, normal, 1.0);

   normal = QVector3D::crossProduct(G, H);
   //Right front
   data.addElement(G, normal, 1.0);
   data.addElement(H, normal, 1.0);
   data.addElement(F, normal, 1.0);

   data.addElement(E, normal, 1.0);
   data.addElement(G, normal, 1.0);
   data.addElement(F, normal, 1.0);

   return data;
}

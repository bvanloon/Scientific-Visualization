#include "gpudata.h"
#include <assert.h>
#include <QDebug>
#include "settings/canvassettings.h"

GPUData::GPUData(GLint drawMode) :
   drawMode(drawMode)
{}

void GPUData::transform(QMatrix4x4 transformation)
{
   transformVectors(&this->vertices, transformation);
   transformVectors(&this->normals, transformation);
}

void GPUData::extend(GPUData data)
{
   assertDrawModesAreEqual(this->drawMode, data.drawMode);
   this->vertices.append(data.getVertices());
   this->normals.append(data.getNormals());
   this->textureCoordinates.append(data.getTextureCoordinates());
}

int GPUData::numElements() const
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

GPUData GPUData::debugSlice()
{
    double xMin = 1.0;
    double xMax = Settings::canvas().size.width() - 1;

    double yMin = 1.0;
    double yMax = Settings::canvas().size.height();

    GPUData data = GPUData(GL_LINES);
    data.addElement(QVector3D(xMin, yMin, 0), QVector3D(0, 0, 1.0), 0.0);
    data.addElement(QVector3D(xMin, yMax, 0), QVector3D(0, 0, 1.0), 0.03);

    data.addElement(QVector3D(xMin, yMax, 0), QVector3D(0, 0, 1.0), 0.03);
    data.addElement(QVector3D(xMax, yMax, 0), QVector3D(0, 0, 1.0), 0.06);

    data.addElement(QVector3D(xMax, yMax, 0), QVector3D(0, 0, 1.0), 0.06);
    data.addElement(QVector3D(xMax, yMin, 0), QVector3D(0, 0, 1.0), 1.0);

    data.addElement(QVector3D(xMax, yMin, 0), QVector3D(0, 0, 1.0), 1.0);
    data.addElement(QVector3D(xMin, yMin, 0), QVector3D(0, 0, 1.0), 0.0);
    return data;
}

void GPUData::transformVectors(QVector<QVector3D> *vector, QMatrix4x4 transformation)
{
   QVector4D transformedPosition;
   for (int i = 0; i < numElements(); i++)
   {
      transformedPosition = transformation * QVector4D(vector->at(i), 1.0);
      vector->replace(i, transformedPosition.toVector3D());
   }
}

GLint GPUData::getDrawMode() const
{
   return drawMode;
}

void GPUData::assertDrawModesAreEqual(GLint thisMode, GLint otherMode)
{
   assert(thisMode == otherMode);
}

#include "gpudata.h"
#include <assert.h>
#include <QDebug>
#include "settings/canvassettings.h"

GPUData::GPUData() :
   drawMode(noDrawMode)
{}

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
   determineDrawMode(this->drawMode, data.drawMode);
   this->vertices.append(data.getVertices());
   this->normals.append(data.getNormals());
   this->textureCoordinates.append(data.getTextureCoordinates());
   this->alphas.append(data.getAlphas());
}

int GPUData::numElements() const
{
   return this->vertices.length();
}

void GPUData::addElement(QVector3D vertex, QVector3D normal, float textureCoordinate, float alpha)
{
   this->vertices.append(vertex);
   this->normals.append(normal);
   this->textureCoordinates.append(textureCoordinate);
   this->alphas.append(alpha);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector3D normal, float textureCoordinate, float alpha)
{
   QVector<QVector3D> normals = QVector<QVector3D>(vertices.size(), normal);
   QVector<float> textureCoordinates = QVector<float>(vertices.size(), textureCoordinate);
   addElements(vertices, normals, textureCoordinates, alpha);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, float textureCoordinate, float alpha)
{
   QVector<float> textureCoordinates = QVector<float>(vertices.size(), textureCoordinate);
   addElements(vertices, normals, textureCoordinates, alpha);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector3D normal, QVector<float> textureCoordinates, float alpha)
{
   QVector<QVector3D> normals = QVector<QVector3D>(vertices.size(), normal);
   addElements(vertices, normals, textureCoordinates, alpha);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates, float alpha)
{
   QVector<float> alphas = QVector<float>(vertices.size(), alpha);
   addElements(vertices, normals, textureCoordinates, alphas);
}

void GPUData::addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates, QVector<float> alphas)
{
   assert(this->vertices.length() == this->normals.length());
   assert(this->vertices.length() == this->textureCoordinates.length());
   assert(this->vertices.length() == this->alphas.length());

   this->vertices.append(vertices);
   this->normals.append(normals);
   this->textureCoordinates.append(textureCoordinates);
   this->alphas.append(alphas);
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

QVector<float> GPUData::getAlphas() const
{
   return alphas;
}

GPUData GPUData::debugSlice()
{
   double xMin = 1.0;
   double xMax = Settings::canvas().size.width() - 1;

   double yMin = 1.0;
   double yMax = Settings::canvas().size.height();

   GPUData data = GPUData(GL_TRIANGLES);
   data.addElement(QVector3D(xMin, yMin, 0), QVector3D(0, 0, 1.0), 0.0);
   data.addElement(QVector3D(xMax, yMin, 0), QVector3D(0, 0, 1.0), 10.0);
   data.addElement(QVector3D(xMin, yMax, 0), QVector3D(0, 0, 1.0), 3.33);

   data.addElement(QVector3D(xMin, yMax, 0), QVector3D(0, 0, 1.0), 3.33);
   data.addElement(QVector3D(xMax, yMin, 0), QVector3D(0, 0, 1.0), 10.0);
   data.addElement(QVector3D(xMax, yMax, 0), QVector3D(0, 0, 1.0), 6.66);

   return data;
}

GPUData GPUData::debugLowerLeftTriangle()
{
   double xMin = 1.0;
   double xMax = Settings::canvas().size.width() - 1;

   double yMin = 1.0;
   double yMax = Settings::canvas().size.height();

   float alpha = 0.25;
   float texture = 0.0;
   float z = -300.0;

   GPUData data = GPUData(GL_TRIANGLES);
   data.addElement(QVector3D(xMin, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   return data;
}

GPUData GPUData::debugUpperLeftTriangle()
{
   double xMin = 1.0;
   double xMax = Settings::canvas().size.width() - 1;

   double yMin = 1.0;
   double yMax = Settings::canvas().size.height();

   float alpha = 0.25;
   float texture = 5.0;
   float z = -200.0;

   GPUData data = GPUData(GL_TRIANGLES);
   data.addElement(QVector3D(xMin, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   return data;
}

GPUData GPUData::debugUpperRightTriangle()
{
   double xMin = 1.0;
   double xMax = Settings::canvas().size.width() - 1;

   double yMin = 1.0;
   double yMax = Settings::canvas().size.height();

   float alpha = 0.25;
   float texture = 10.0;
   float z = -100.0;

   GPUData data = GPUData(GL_TRIANGLES);
   data.addElement(QVector3D(xMin, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   return data;
}

GPUData GPUData::debugLowerRightTriangle()
{
   double xMin = 1.0;
   double xMax = Settings::canvas().size.width() - 1;

   double yMin = 1.0;
   double yMax = Settings::canvas().size.height();

   float alpha = 0.25;
   float texture = 7.4;
   float z = 0.0;

   GPUData data = GPUData(GL_TRIANGLES);
   data.addElement(QVector3D(xMin, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   data.addElement(QVector3D(xMin, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMin, z), QVector3D(0, 0, 1.0), texture, alpha);
   data.addElement(QVector3D(xMax, yMax, z), QVector3D(0, 0, 1.0), texture, alpha);

   return data;
}

bool GPUData::isEmpty()
{
   return this->numElements() == 0;
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

int GPUData::determineDrawMode(GLint thisMode, GLint otherMode)
{
   if ((thisMode != noDrawMode) && (otherMode != noDrawMode))
   {
      assert(thisMode == otherMode);
      return thisMode;
   }
   if (thisMode != noDrawMode) return thisMode;

   if (otherMode != noDrawMode) return otherMode;

   //We are combining two empty GPUData objects.
   return noDrawMode;
}

#ifndef GPUDATA_H
#define GPUDATA_H

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class GPUData
{
   public:
      GPUData(GLint drawMode);

      void transform(QMatrix4x4 transformation);

      void addElement(QVector3D vertex, QVector3D normal, float textureCoordinate, float alpha = 1.0);

      void addElements(QVector<QVector3D> vertices, QVector3D normal, float textureCoordinate, float alpha = 1.0);
      void addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, float textureCoordinate, float alpha = 1.0);
      void addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates, float alpha = 1.0);
      void addElements(QVector<QVector3D> vertices, QVector3D normal, QVector<float> textureCoordinates, float alpha = 1.0);
      void addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates, QVector<float> alphas);

      void extend(GPUData data);

      int numElements() const;

      GLint getDrawMode() const;

      QVector<QVector3D> getVertices() const;

      QVector<float> getTextureCoordinates() const;

      QVector<QVector3D> getNormals() const;

      QVector<float> getAlphas() const;

      static GPUData debugSlice();

   private:
      GLint drawMode;

      QVector<QVector3D> vertices;
      QVector<float> textureCoordinates;
      QVector<QVector3D> normals;
      QVector<float> alphas;

      void transformVectors(QVector<QVector3D> *vector, QMatrix4x4 transformation);

      void assertDrawModesAreEqual(GLint thisMode, GLint otherMode);
};

#endif // GPUDATA_H

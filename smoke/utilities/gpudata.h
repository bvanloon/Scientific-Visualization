#ifndef GPUDATA_H
#define GPUDATA_H

#include <QVector>
#include <QVector3D>

class GPUData
{
   public:
      GPUData();

      void extend(GPUData data);

      int numElements();

      void addElement(QVector3D vertex, QVector3D normal, float textureCoordinate);

      void addElements(QVector<QVector3D> vertices, QVector3D normal, float textureCoordinate);

      void addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, float textureCoordinate);

      void addElements(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<float> textureCoordinates);

      void addElements(QVector<QVector3D> vertices, QVector3D normal, QVector<float> textureCoordinates);

      QVector<QVector3D> getVertices() const;

      QVector<float> getTextureCoordinates() const;

      QVector<QVector3D> getNormals() const;

   private:
      QVector<QVector3D> vertices;
      QVector<float> textureCoordinates;
      QVector<QVector3D> normals;
};

#endif // GPUDATA_H

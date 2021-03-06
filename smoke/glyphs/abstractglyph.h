#ifndef ABSTRACTGLYPH_H
#define ABSTRACTGLYPH_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <QVector>
#include <QVector3D>
#include "utilities/gpudata.h"

class AbstractGlyph
{
   public:
      AbstractGlyph();

      GPUData toGPUData(float textureCoordinate, float alpha = 1.0);

   protected:
      QVector<QVector3D> normals;
      QVector<QVector3D> vertices;

      virtual GLint getDrawMode() const = 0;

      void addVertex(QVector3D vertex, QVector3D normal);

      void addVertices(QVector<QVector3D> vertices, QVector3D normal);

      void addVertices(QVector<QVector3D> vertices, QVector<QVector3D> normals);

      float computeNormalizedMagnitude(QVector3D direction);

      float computeBaseSize(float cellRatio);

   private:
};

#endif // ABSTRACTGLYPH_H

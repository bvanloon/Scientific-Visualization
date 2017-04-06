#ifndef GLYPHS_CONE_H
#define GLYPHS_CONE_H

#include "glyphs/abstractglyph.h"
#include "utilities/mesh.h"

class Cone : public AbstractGlyph
{
   public:
      Cone(QVector3D position, QVector3D direction);

   protected:
      GLint getDrawMode() const;

   private:

      mesh::TriangleMesh *mesh;
      float normalizedMagnitude;
      QVector3D position;
      QVector3D normalizedDirection;

      static const double maxCellRatio;

      float computeScalingFactor();

      float radiansToDegrees(float radians);

      void transform();

      QMatrix4x4 translationMatrix();

      QMatrix4x4 scalingMatrix();

      QMatrix4x4 rotationMatrix();
};

#endif // GLYPHS_CONE_H

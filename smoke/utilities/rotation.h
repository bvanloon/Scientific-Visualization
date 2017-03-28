#ifndef ROTATION_H
#define ROTATION_H

#include <QMatrix4x4>

class Rotation
{
   public:
      enum axis
      {
         xAxis, yAxis, zAxis
      };

      Rotation(int xAngle = 0, int yAngle = 0, int zAngle = 0);

      int x() const;

      void setX(int value);

      int y() const;

      void setY(int value);

      int z() const;

      void setZ(int value);

      void setRotation(Rotation::axis axis, int angle);

      QMatrix4x4 matrix();

   private:

      int xAngle;

      int yAngle;
      int zAngle;
};

#endif // ROTATION_H

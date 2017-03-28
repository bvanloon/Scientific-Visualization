#include "rotation.h"

Rotation::Rotation(int x, int y, int z) :
   xAngle(x),
   yAngle(y),
   zAngle(z)
{}

int Rotation::x() const
{
   return xAngle;
}

int Rotation::y() const
{
   return yAngle;
}

void Rotation::setY(int value)
{
   yAngle = value;
}

int Rotation::z() const
{
   return zAngle;
}

void Rotation::setZ(int value)
{
    zAngle = value;
}

void Rotation::setRotation(Rotation::axis axis, int angle)
{
    switch(axis){
    case Rotation::xAxis:
        this->setX(angle);
        return;
    case Rotation::yAxis:
        this->setY(angle);
        return;
    case Rotation::zAxis:
        this->setZ(angle);
        return;
    }
}

QMatrix4x4 Rotation::matrix()
{
   QMatrix4x4 rotationMatrix;

   rotationMatrix.setToIdentity();
   rotationMatrix.rotate(this->x(), 1.0, 0.0, 0.0);
   rotationMatrix.rotate(this->y(), 0.0, 1.0, 0.0);
   rotationMatrix.rotate(this->z(), 0.0, 0.0, 1.0);
   return rotationMatrix;
}

void Rotation::setX(int value)
{
   xAngle = value;
}

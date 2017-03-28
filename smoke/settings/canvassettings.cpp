#include "canvassettings.h"
#include <QDebug>

Settings::Canvas::Canvas(QObject *parent) :
   QObject(parent),
   size(506, 500)
{}

const Settings::Canvas& Settings::Canvas::instance()
{
   static Canvas instance;

   return instance;
}

void Settings::Canvas::onWindowResized(int width, int height)
{
   QSizeF oldSize = this->size;

   size.setWidth(width);
   size.setHeight(height);
   QSizeF newSize = this->size;

   emit windowResized(oldSize, newSize);
}

void Settings::Canvas::onRotationChanged(Rotation::axis axis, int newAngle)
{
   qDebug() << "Settings::Canvas::onRotationChanged axis: " << axis << "angle: " << newAngle;
   this->rotation.setRotation(axis, newAngle);
   qDebug() << "New Rotation: " << rotation.x() << rotation.y() << rotation.z();
}

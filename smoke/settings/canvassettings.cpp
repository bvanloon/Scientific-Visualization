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

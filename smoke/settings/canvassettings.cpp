#include "canvassettings.h"
#include <QDebug>

Settings::Canvas::Canvas(QObject *parent) :
   QObject(parent),
   size(506, 500),
   scalingFactor(Settings::defaults::canvas::scalingFactor),
   rotation(Settings::defaults::canvas::rotation),
   panningPosition(Settings::defaults::canvas::panningPosition)
{}

const Settings::Canvas& Settings::Canvas::instance()
{
   static Canvas instance;

   return instance;
}

QPointF Settings::Canvas::convertToNormalCoordinates(QPointF openGLCoordinates) const
{
   return convertToNormalCoordinates(QVector3D(openGLCoordinates)).toPointF();
}

QVector3D Settings::Canvas::convertToNormalCoordinates(QVector3D openGLCoordinates) const
{
   QVector3D normalCoordinates = QVector3D(
                openGLCoordinates.x(),
                Settings::canvas().size.height() - openGLCoordinates.y(),
                0.0);

   return normalCoordinates;
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
   this->rotation.setRotation(axis, newAngle);
   emit updateModelViewMatrix();
}

void Settings::Canvas::onScalingFactorChanged(double newScalingFactor)
{
   this->scalingFactor = newScalingFactor;
   emit updateModelViewMatrix();
   emit scalingFactorChanged(newScalingFactor);
}

void Settings::Canvas::onPanningPositionChanged(QVector3D newDirection)
{
   this->panningPosition = this->panningPosition + this->panningFactor * newDirection;

   emit updateModelViewMatrix();
}

void Settings::Canvas::onResetView()
{
   this->scalingFactor = Settings::defaults::canvas::scalingFactor;
   this->panningPosition = Settings::defaults::canvas::panningPosition;
   this->rotation = Settings::defaults::canvas::rotation;

   emit scalingFactorChanged(this->scalingFactor);
   emit rotationChanged(this->rotation);
   emit updateModelViewMatrix();
}

#include "canvassettings.h"
#include <QDebug>

Settings::Canvas::Canvas(QObject *parent) :
   QObject(parent),
   size(506, 500),
   rotation(Settings::defaults::canvas::rotation),
   scalingFactor(Settings::defaults::canvas::scalingFactor),
   panningPosition(Settings::defaults::canvas::panningPosition)
{}

void Settings::Canvas::setPanningPosition(QVector3D position)
{
   this->panningPosition = position;
   emit updateModelViewMatrix();
}

void Settings::Canvas::setRotation(int xAngle, int yAngle, int zAngle)
{
   setRotation(Rotation(xAngle, yAngle, zAngle));
}

void Settings::Canvas::setRotation(Rotation rotation)
{
   this->rotation = rotation;
   emit rotationChanged(this->rotation);
   emit updateModelViewMatrix();
}

void Settings::Canvas::setScaling(float scalingFactor)
{
   this->scalingFactor = scalingFactor;
   emit scalingFactorChanged(this->scalingFactor);
   emit updateModelViewMatrix();
}

void Settings::Canvas::toggleAllEngines(bool toggle)
{
   toggleAll2DEngines(toggle);
   toggleAll3DEngines(toggle);
}

void Settings::Canvas::toggleAll3DEngines(bool toggle)
{
   toggleAllSliceEngines(toggle);
   emit engineToggled(Settings::engines::EnginesTypes::streakObjects, toggle);
}

void Settings::Canvas::toggleAllSliceEngines(bool toggle)
{
   emit engineToggled(Settings::engines::EnginesTypes::smokeSlices, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::glyphSlices, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::streamLineSlices, toggle);
}

void Settings::Canvas::toggleAll2DEngines(bool toggle)
{
   emit engineToggled(Settings::engines::EnginesTypes::smoke, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::glyphs, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::streamLines, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::seedPoints, toggle);
}

const Settings::Canvas& Settings::Canvas::instance()
{
   static Canvas instance;

   return instance;
}

QPointF Settings::Canvas::convertToNormalCoordinates(QPointF openGLCoordinates) const
{
   return convertToNormalCoordinates(QVector3D(openGLCoordinates)).toPointF();
}

QPoint Settings::Canvas::convertToNormalCoordinates(QPoint openGLCoordinates) const
{
   return convertToNormalCoordinates(QVector3D(openGLCoordinates)).toPoint();
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
   emit windowResized(newSize);
   emit clearCache();
}

void Settings::Canvas::onRotationChanged(Rotation::axis axis, int newAngle)
{
   this->rotation.setRotation(axis, newAngle);
   emit updateModelViewMatrix();
}

void Settings::Canvas::onScalingFactorChanged(double newScalingFactor)
{
   setScaling(newScalingFactor);
}

void Settings::Canvas::onPanningPositionChanged(QVector3D newDirection)
{
   setPanningPosition(this->panningPosition + this->panningFactor * newDirection);
}

void Settings::Canvas::onResetView()
{
   setScaling(Settings::defaults::canvas::scalingFactor);
   setPanningPosition(Settings::defaults::canvas::panningPosition);
   setRotation(Settings::defaults::canvas::rotation);
}

void Settings::Canvas::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   if (checked) emit clearCache(engine);
   emit engineToggled(engine, checked);
}

void Settings::Canvas::onToggleAllEngines(bool toggle)
{
   toggleAllEngines(toggle);
}

void Settings::Canvas::onToggleAll3DEngines(bool toggle)
{
   toggleAll3DEngines(toggle);
}

void Settings::Canvas::onToggleAllSliceEngines(bool toggle)
{
   toggleAllSliceEngines(toggle);
}

void Settings::Canvas::onToggleAll2DEngines(bool toggle)
{
   toggleAll2DEngines(toggle);
}

void Settings::Canvas::onSetViewMatrixToTopDownView()
{
   setScaling(1.0);
   setPanningPosition(QVector3D(0.0, 0.0, 0.0));
   setRotation(0, 0, 0);
}

void Settings::Canvas::onSetViewMatrixToSideView()
{
   setScaling(0.67);
   setPanningPosition(QVector3D(0.0, 0.0, 0.0));
   setRotation(279, 180, 308);
}

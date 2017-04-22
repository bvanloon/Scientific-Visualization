#ifndef CANVASS_H
#define CANVASS_H

#include <QObject>
#include <QSize>
#include <QPointF>
#include <QVector3D>
#include "utilities/rotation.h"

#include "settings/settings.h"

class Settings::Canvas : public QObject
{
   Q_OBJECT

   public:

      static const Canvas& instance();

      QSize size;
      Rotation rotation;
      double scalingFactor;
      QVector3D panningPosition;

      QPointF convertToNormalCoordinates(QPointF openGLCoordinates) const;
      QPoint convertToNormalCoordinates(QPoint openGLCoordinates) const;
      QVector3D convertToNormalCoordinates(QVector3D openGLCoordinates) const;

   signals:
      void windowResized(QSizeF oldSize, QSizeF newSize);
      void windowResized(QSizeF newSize);

      void updateModelViewMatrix();

      void scalingFactorChanged(double newScalingFactor);

      void rotationChanged(Rotation rotation);

      void engineToggled(Settings::engines::EnginesTypes engine, bool toggle);

      void clearCache();
      void clearCache(Settings::engines::EnginesTypes engine);

   public slots:
      void onWindowResized(int width, int height);

      void onRotationChanged(Rotation::axis axis, int newAngle);

      void onScalingFactorChanged(double newScalingFactor);

      void onPanningPositionChanged(QVector3D newDirection);

      void onResetView();

      void onEngineToggled(Settings::engines::EnginesTypes engine, bool checked);

      void onToggleAllEngines(bool toggle);
      void onToggleAll3DEngines(bool toggle);
      void onToggleAllSliceEngines(bool toggle);
      void onToggleAll2DEngines(bool toggle);

      void onSetViewMatrixToTopDownView();

      void onSetViewMatrixToSideView();

   private:
      explicit Canvas(QObject *parent = 0);

      double panningFactor = 10;

      void setPanningPosition(QVector3D position);
      void setRotation(int xAngle, int yAngle, int zAngle);
      void setRotation(Rotation rotation);
      void setScaling(float scalingFactor);

      void toggleAllEngines(bool toggle);
      void toggleAll3DEngines(bool toggle);
      void toggleAllSliceEngines(bool toggle);
      void toggleAll2DEngines(bool toggle);

      Canvas(Canvas const&) = delete;
      void operator=(Canvas const&) = delete;
};

#endif // CANVASS_H
